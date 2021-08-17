import pandas as pd
import matplotlib.pyplot as plt
import math
import matplotlib.patches as mpatches


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
                else:
                    timings_type = test_inst['heap']

                timings_type.append(
                    (n, m, name, [float(x) for x in content[1].split()]))

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
        print(index, data_graph['array'])


for (inst, inst_name) in [('alue', 'ALUE'), ('alut', 'ALUT'), ('dmxa', 'DMXA'), ('test_set1', 'test_set1'),
                          ('test_set2', 'test_set2')]:
    inst_data = data[inst]

    for inst_type in ['array', 'heap']:
        inst_data_impl = inst_data[inst_type]
        data_nums = []
        for impl in inst_data_impl:
            (n, m, name, actual_data) = impl
            df = pd.DataFrame.from_dict(actual_data)
            data_nums.append((n, m, name, float(df.median())))

        data_nums.sort()

        data_names = [x[2] for x in data_nums]

        if inst_type == 'array':
            data_ratio = [x[0] * x[0] for x in data_nums]
            complexidade = 'n²'
        else:
            data_ratio = [x[1] * math.log(x[0]) for x in data_nums]
            complexidade = 'm log n'

        data_data = [x[3] for x in data_nums]
        data_df = pd.DataFrame({'inst': data_names, 'expected': data_ratio, 'actual': data_data})

        data_df['ratio'] = data_df.expected / data_df.actual

        ax = data_df.plot(figsize=(19.2, 10.8), x='inst', y='expected', logy=True, fontsize=20,
                          linewidth=7, color='#FF7F0E', legend=False)
        ax.set_ylabel(f'Complexidade {complexidade}', fontdict={'size': 24})
        ax.set_xlabel(None)

        ax = data_df.actual.plot(x='inst', logy=True, secondary_y=True, rot=45, fontsize=20, linewidth=7,
                                 color='#1F77B4')
        ax.set_ylabel('Tempo em segundos', fontdict={'size': 24})

        plt.title(f'Comparação tempo real e complexidade teórica\n{inst_name} com {inst_type}\n',
                  fontdict={'size': 32})

        plt.legend(prop={'size': 18}, handles=[
            mpatches.Patch(color='#FF7F0E', label=f'Complexidade {complexidade}'),
            mpatches.Patch(color='#1F77B4', label='Tempo em segundos'),
        ])

        plt.tight_layout()
        plt.savefig(f'comp/{inst}_{inst_type}')
        plt.close()
