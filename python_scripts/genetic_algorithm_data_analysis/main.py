from mpl_toolkits.mplot3d import Axes3D
import matplotlib.pyplot as plt
import pandas as pd


def read_csv_to_data_frame(file_path):
    df = pd.read_csv(file_path, header=0, skiprows=2)
    df['Mean relative error [%]'] = (100 * (df['Mean algorithm solution'] - df['Optimal solution'])) / df[
        'Optimal solution']
    # with pd.option_context('display.max_rows', None, 'display.max_columns', None):
    #     print(df.dtypes)
    #     print(df.head())
    return df


def scatter_plot_parameter_analysis(df, xlabel='Parametr', ylabel='Błąd średni względny [%]', title=None,
                                    size_param=0.5, legend_loc='best'):
    for instance in df['Instance size'].unique():
        df_instance = df[df['Instance size'] == instance]
        plt.scatter(df_instance['Parameter'], df_instance['Mean relative error [%]'],
                    s=df_instance['Time'] ** size_param, alpha=1, edgecolors="black", linewidth=1,
                    label="Rozmiar instancji: " + str(instance))

    plt.xlabel(xlabel)
    plt.ylabel(ylabel)
    plt.title(title)
    plt.legend(loc=legend_loc, fontsize='xx-small')
    plt.grid(True)

    plt.show()


def plot_multiple(plotting_data, legend_location='best', x_step=1, y_column=None):
    x_min = None
    x_max = None
    for plt_data in plotting_data:
        plt.plot(plt_data['df']['Instance size'], plt_data['df'][y_column], plt_data['style'], label=plt_data['label'])
        x_min = plt_data['df']['Instance size'].min()
        x_max = plt_data['df']['Instance size'].max()

    plt.xticks(range(x_min, x_max + x_step, x_step))
    # plt.ticklabel_format(axis='y', style='sci', scilimits=(3, 3))
    plt.grid(True)

    plt.xlabel('Rozmiar instancji')
    if y_column == 'Time':
        plt.ylabel('Czas wykonania [ms]')
    else:
        plt.ylabel('Błąd średni względny [%]')
    plt.legend(loc=legend_location)

    plt.show()


def export_benchmark_data_to_csv():
    ga_benchmark_df = read_csv_to_data_frame('data/genetic_algorithm/ga_time_benchmark.csv')
    ga_benchmark_df = ga_benchmark_df.rename(
        columns={"Time": "GA: czas [ms]", "Mean relative error [%]": "GA: błąd średni względny [%]",
                 "Instance size": 'Rozmiar instancji'})

    ts_benchmark_df = read_csv_to_data_frame('data/local_search/benchmarks/tabu_search_matrix_benchmark.csv')
    ts_benchmark_df = ts_benchmark_df.rename(
        columns={"Time": "TS: czas [ms]", "Mean relative error [%]": "TS: błąd średni względny [%]"})

    merged_df = pd.DataFrame(ga_benchmark_df['Rozmiar instancji'])
    merged_df = merged_df.join(ga_benchmark_df['GA: czas [ms]'])
    merged_df = merged_df.join(ts_benchmark_df['TS: czas [ms]'])
    merged_df = merged_df.join(ga_benchmark_df['GA: błąd średni względny [%]'])
    merged_df = merged_df.join(ts_benchmark_df['TS: błąd średni względny [%]'])
    merged_df = merged_df.round(
        {'GA: czas [ms]': 2, 'TS: czas [ms]': 2, 'GA: błąd średni względny [%]': 2, 'TS: błąd średni względny [%]': 2})

    merged_df.to_csv('data/genetic_algorithm/benchmark_table_ga_ts.csv', index=False, float_format='%.2f')


# Script #
# Genetic algorithm
# scatter_plot_parameter_analysis(read_csv_to_data_frame('data/genetic_algorithm/crossover_probability.csv'),
#                                 xlabel="Prawdopodobieństwo krzyżowania")
# scatter_plot_parameter_analysis(read_csv_to_data_frame('data/genetic_algorithm/elites.csv'),
#                                 xlabel="Liczba osobników elitarnych")
# scatter_plot_parameter_analysis(read_csv_to_data_frame('data/genetic_algorithm/generations.csv'),
#                                 xlabel="Liczba generacji")
# scatter_plot_parameter_analysis(read_csv_to_data_frame('data/genetic_algorithm/mutation_probability.csv'),
#                                 xlabel="Prawdopodobieństwo mutacji")
# scatter_plot_parameter_analysis(read_csv_to_data_frame('data/genetic_algorithm/population_size.csv'),
#                                 xlabel="Rozmiar populacji")
# scatter_plot_parameter_analysis(read_csv_to_data_frame('data/genetic_algorithm/tournament_size.csv'),
#                                 xlabel="Liczba osobników w rundzie turniejowej")

benchmark_dfs = (
    {'df': read_csv_to_data_frame('data/genetic_algorithm/ga_time_benchmark.csv'),
     'label': "Algorytm genetyczny", 'style': 'gs-'},
    # {'df': read_csv_to_data_frame('data/local_search/benchmarks/simulated_annealing_benchmark.csv'),
    #  'label': 'Symulowane wyżarzanie', 'style': 'b^-'},
    {'df': read_csv_to_data_frame('data/local_search/benchmarks/tabu_search_matrix_benchmark.csv'),
     'label': 'Poszukiwanie z zakazami', 'style': 'ro-'}
)

plot_multiple(benchmark_dfs, x_step=10, y_column='Time')
plot_multiple(benchmark_dfs, x_step=10, y_column='Mean relative error [%]')

# export_benchmark_data_to_csv()
