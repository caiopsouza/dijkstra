import pprint

import pandas as pd
import math
import matplotlib.pyplot as plt


def load_data():
    data = {
        'alue': {'array': [], 'heap': []},
        'alut': {'array': [], 'heap': []},
        'dmxa': {'array': [], 'heap': []},
        'test_set1': {'array': [], 'heap': []},
        'test_set2': {'array': [], 'heap': []},
    }

    with open('data/dijkstra-2021-08-05.txt') as f:
        for content in f:
            if 'instances' in content:
                if 'alue' in content:
                    test_inst = data['alue']
                elif 'alut' in content:
                    test_inst = data['alut']
                elif 'dmxa' in content:
                    test_inst = data['dmxa']
                elif 'test_set1' in content:
                    test_inst = data['test_set1']
                else:
                    test_inst = data['test_set2']

                name = content.split('/')[-1][:-5]
                continue

            if 'array' in content or 'heap' in content:
                content = content.split(':')

                dims = content[0][17:][:-1].split(',')
                m = int(dims[0])
                n = int(dims[1].strip())

                if 'array' in content[0]:
                    timings_type = test_inst['array']
                    ratio = n * n
                else:
                    timings_type = test_inst['heap']
                    ratio = m * math.log(n, m / n)

                timings_type.append(
                    (n, name, [float(x) for x in content[1].split()], [float(x) / ratio for x in content[1].split()]))

    return data


def plot(timing, problem, algo, showfliers, title, ylabel, filename):
    frame = pd.DataFrame.from_dict(timing)
    plt.figure(figsize=(14.4, 9))
    frame.boxplot(rot=45, showfliers=showfliers)
    plt.title(f'Benchmark{title}. Instância {problem}. Dijkstra com {algo}.')
    plt.ylabel('Tempo em segundos' + ylabel)
    plt.savefig(filename)
    plt.close()


data = load_data()
for (problem, problem_data) in data.items():
    for (algo, timings) in problem_data.items():
        timings.sort()
        linear = {name: timing for (_, name, timing, _) in timings}
        ratio = {name: timing for (_, name, _, timing) in timings}

        linear_filename = 'res/linear_' + problem + '_' + algo + '_'
        ratio_filename = 'res/ratio_' + problem + '_' + algo + '_'

        if problem[0] != 't':
            problem = problem.upper()

        if algo == 'array':
            divisor = ' dividido por n²'
        else:
            divisor = ' dividido por m*log(n,m/n)'

        plot(linear, problem, algo, True, '', '', linear_filename + 'outliers')
        plot(linear, problem, algo, False, '', '', linear_filename + 'no_outliers')

        plot(ratio, problem, algo, True, ' normalizado', divisor, ratio_filename + 'outliers')
        plot(ratio, problem, algo, False, ' normalizado', divisor, ratio_filename + 'no_outliers')
