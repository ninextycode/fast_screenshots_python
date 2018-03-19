import time
import cv2
import capturer as cp


def was_space_pressed():
    space = ' '
    return cv2.waitKey(1) & 0xFF == ord(space)


fourcc = cv2.VideoWriter_fourcc(*'XVID')
dim = (1300, 700)
offset = (0, 0)

fps = 20
period = 1 / fps

out = cv2.VideoWriter('output.avi',
                      fourcc, fps,
                      dim)

capt = cp.Capturer(*(offset + dim))

last_time = time.time()

while True:
    # wait to get correct fps
    dt = time.time() - last_time
    while dt < period:
        dt = time.time() - last_time
    last_time = time.time()

    frame = capt.get_fast_screenshot()

    print(1 / dt)

    [b, g, r, a] = cv2.split(frame)
    frame = cv2.merge([b, g, r])

    out.write(frame)
    cv2.imshow("frame", frame)

    if was_space_pressed():
        break

# Release everything if job is finished
out.release()
cv2.destroyAllWindows()
