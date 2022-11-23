import time

import os
import pandas as pd

import matplotlib.pyplot as plt 

tempos = {}
t_counts = [1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 768, 1024, 1536]

for t in t_counts:
    tempo_local = []
    for i in range(3):
        t1 = time.time()
        os.system(f'go run main.go euler.go 1000 {t}')
        t2 = time.time()
        tf = t2 - t1
        tempo_local.append(tf)
    
    print(t, tempo_local)
    tempos[str(t)] = tempo_local 

data = {}
data['t1'] = []
data['t2'] = []
data['t3'] = []
data['t_mean'] = []
data['speedup'] = []

mean_0 = (tempos['1'][0] + tempos['1'][1] + tempos['1'][2]) / 3

for i in tempos:
    data['t1'].append(tempos[i][0])
    data['t2'].append(tempos[i][1])
    data['t3'].append(tempos[i][2])
    
    mean = (tempos[i][0] + tempos[i][1] + tempos[i][2]) / 3
    
    data['t_mean'].append(mean)
    data['speedup'].append(mean_0 / mean)

df = pd.DataFrame(data)
df.to_csv('stats.csv', index=False)
print('saved stats.csv')
print(df.to_markdown(index=False))

plt.figure()
plt.plot(t_counts, df['speedup'])

plt.ylabel('Speedup')
plt.xlabel('Threads')

plt.savefig('speedup_plot.png')
print('saved speedup_plot.png')