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
                n = int(dims[0])
                m = int(dims[1].strip())

                if 'array' in content[0]:
                    timings_type = test_inst['array']
                    ratio = n * n
                else:
                    timings_type = test_inst['heap']
                    ratio = m * math.log2(n)

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


def main():
    comparing = {}

    for (problem, problem_data) in data.items():
        for (algo, timings) in problem_data.items():
            timings.sort()
            linear = {name: timing for (_, name, timing, _) in timings}
            ratio = {name: timing for (_, name, _, timing) in timings}

            for (inst, timing) in linear.items():
                if inst not in comparing:
                    comparing[inst] = {}

                comparing_time = comparing[inst]
                comparing_time[algo] = {inst: float(pd.DataFrame(timing).mean())}

            linear_filename = 'res/linear_' + problem + '_' + algo + '_'
            ratio_filename = 'res/ratio_' + problem + '_' + algo + '_'

            if problem[0] != 't':
                problem_norm = problem.upper()

            if algo == 'array':
                divisor = ' dividido por n²'
            else:
                divisor = ' dividido por m*log₂n'

            plot(linear, problem_norm, algo, True, '', '', linear_filename + 'outliers')
            plot(linear, problem_norm, algo, False, '', '', linear_filename + 'no_outliers')

            plot(ratio, problem_norm, algo, True, ' normalizado', divisor, ratio_filename + 'outliers')
            plot(ratio, problem_norm, algo, False, ' normalizado', divisor, ratio_filename + 'no_outliers')

    def filter(inst, algo):
        res = []
        for (k, v) in comparing.items():
            if inst in k:
                res.append(v[algo])
        return res

    def create_data(inst):
        array = filter(inst, 'array')
        heap = filter(inst, 'heap')

        index = [list(l)[0] for l in array]

        array = [list(l.values())[0] for l in array]
        heap = [list(l.values())[0] for l in heap]

        data_graph = {'array': array, 'heap': heap}

        return index, data_graph

    for (inst, inst_name) in [('alue', 'ALUE'), ('alut', 'ALUT'), ('dmxa', 'DMXA'), ('s1', 'test_set1'),
                              ('s2', 'test_set2')]:
        index, data_graph = create_data(inst)
        df = pd.DataFrame(data_graph, index=index)
        plt.figure()
        ax = df.plot(rot=45, figsize=(12.8, 8))
        ax.set_yscale('log')
        plt.title(f'Comparação tempo execução. Instâncias {inst_name}. Escala logarítmica')
        plt.ylabel('Tempo em segundos.')
        plt.savefig('res/comp_' + inst)
        plt.close()


main()
