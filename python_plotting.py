import numpy as np
import matplotlib.pyplot as plt

f = open("temperature.txt", 'r')
s = f.read().split(' ')
f.close()
s.remove('')
temp = np.array(s).astype(dtype = float)

f = open("T_shape.txt", 'r')
s = f.read().split(' ')
f.close()
s.remove('')
rows, cols, dt = int(s[0]), int(s[1]), float(s[2])
temp = temp.reshape((rows, cols))


f = open("time.txt", 'r')
s = f.read().split(' ')
f.close()
s.remove('')
time = np.array(s).astype(float)

assert(len(time) == len(temp[1]))
assert(cols == len(time))

print(rows, cols)



for t in range(0,25, 5):
    plt.plot(temp[:,t], label = f'T at time t = {t*dt}')
plt.legend()
plt.show()


