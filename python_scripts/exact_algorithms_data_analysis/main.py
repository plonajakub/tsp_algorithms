import pandas
import matplotlib.pyplot as plt


def get_measurement_points_from_csv(file_path):
    df = pandas.read_csv(file_path, header=0, skiprows=2)
    # print(df.dtypes)

    data_dict = df.to_dict()
    points = {'x': [], 'y': []}
    for key in data_dict.keys():
        try:
            points['x'].append(int(key))
            points['y'].append(float(data_dict[key][0]))
        except ValueError:
            print(key, 'key in', file_path, 'was skipped')

    return points


def plot_multiple(plotting_data, legend_location='upper left', x_step=1):
    x_min = 1 << 30
    x_max = 0
    for plt_data in plotting_data:
        plt.plot(plt_data['points']['x'], plt_data['points']['y'], plt_data['style'], label=plt_data['label'])
        if plt_data['points']['x'][0] < x_min:
            x_min = plt_data['points']['x'][0]
        if plt_data['points']['x'][-1] > x_max:
            x_max = plt_data['points']['x'][-1]

    plt.xticks(range(x_min, x_max + x_step, x_step))
    plt.ticklabel_format(axis='y', style='sci', scilimits=(3, 3))
    plt.grid(True)

    plt.xlabel('Rozmiar instancji')
    plt.ylabel('Czas wykonania [ms]')
    plt.legend(loc=legend_location)

    plt.show()


data = {'bf-s': get_measurement_points_from_csv('csv_files/brute_force_swap.csv'),
        'bf-t': get_measurement_points_from_csv('csv_files/brute_force_tree.csv'),
        'dp': get_measurement_points_from_csv('csv_files/dynamic_programming.csv'),
        'bb': get_measurement_points_from_csv('csv_files/branch_and_bound_0h.csv'),
        'bb-nn': get_measurement_points_from_csv('csv_files/branch_and_bound_nn.csv'),
        'bb-g': get_measurement_points_from_csv('csv_files/branch_and_bound_g.csv'),
        'bb-nn-g': get_measurement_points_from_csv('csv_files/branch_and_bound_nn_g.csv')}

# print(data)

plot_multiple(({'points': data['bf-s'], 'style': 'ro-', 'label': 'BF (swap)'},
               {'points': data['dp'], 'style': 'gs-', 'label': 'DP (Held-Karp)'},
               {'points': data['bb-nn-g'], 'style': 'b^-', 'label': 'B&B (Little; NN; G)'}),
              x_step=2,
              legend_location='upper right')

plot_multiple(({'points': data['bf-s'], 'style': 'ro-', 'label': 'BF (swap)'},
               {'points': data['bf-t'], 'style': 'gs-', 'label': 'BF (DFS)'}),
              legend_location='upper left')

plot_multiple(({'points': data['bb'], 'style': 'ro-', 'label': 'B&B (Little)'},
               {'points': data['bb-nn'], 'style': 'gs-', 'label': 'B&B (Little; NN)'},
               {'points': data['bb-g'], 'style': 'b^-', 'label': 'B&B (Little; G)'},
               {'points': data['bb-nn-g'], 'style': 'ys-', 'label': 'B&B (Little; NN; G)'}),
              x_step=2,
              legend_location='upper right')

plot_multiple(({'points': data['bf-s'], 'style': 'bo-', 'label': 'BF (swap)'},),
              x_step=1,
              legend_location='upper left')

plot_multiple(({'points': data['bf-t'], 'style': 'bo-', 'label': 'BF (DFS)'},),
              x_step=1,
              legend_location='upper left')

plot_multiple(({'points': data['dp'], 'style': 'bo-', 'label': 'DP (Held-Karp)'},),
              x_step=1,
              legend_location='upper left')

plot_multiple(({'points': data['bb'], 'style': 'bo-', 'label': 'B&B (Little)'},),
              x_step=2,
              legend_location='upper right')

plot_multiple(({'points': data['bb-nn'], 'style': 'bo-', 'label': 'B&B (Little; NN)'},),
              x_step=2,
              legend_location='upper right')

plot_multiple(({'points': data['bb-g'], 'style': 'bo-', 'label': 'B&B (Little; G)'},),
              x_step=2,
              legend_location='upper right')

plot_multiple(({'points': data['bb-nn-g'], 'style': 'bo-', 'label': 'B&B (Little; NN; G)'},),
              x_step=2,
              legend_location='upper right')
