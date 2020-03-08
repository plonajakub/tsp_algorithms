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
    sa_benchmark_df = read_csv_to_data_frame('data/benchmarks/simulated_annealing_benchmark.csv')
    sa_benchmark_df = sa_benchmark_df.rename(
        columns={"Time": "SA: czas [ms]", "Mean relative error [%]": "SA: błąd średni względny [%]",
                 "Instance size": 'Rozmiar instancji'})

    tsl_benchmark_df = read_csv_to_data_frame('data/benchmarks/tabu_search_list_benchmark.csv')
    tsl_benchmark_df = tsl_benchmark_df.rename(
        columns={"Time": "TSL: czas [ms]", "Mean relative error [%]": "TSL: błąd średni względny [%]"})

    tsm_benchmark_df = read_csv_to_data_frame('data/benchmarks/tabu_search_matrix_benchmark.csv')
    tsm_benchmark_df = tsm_benchmark_df.rename(
        columns={"Time": "TSM: czas [ms]", "Mean relative error [%]": "TSM: błąd średni względny [%]"})

    merged_df = pd.DataFrame(sa_benchmark_df['Rozmiar instancji'])
    merged_df = merged_df.join(sa_benchmark_df['SA: czas [ms]'])
    merged_df = merged_df.join(tsl_benchmark_df['TSL: czas [ms]'])
    merged_df = merged_df.join(tsm_benchmark_df['TSM: czas [ms]'])
    merged_df = merged_df.join(sa_benchmark_df['SA: błąd średni względny [%]'])
    merged_df = merged_df.join(tsl_benchmark_df['TSL: błąd średni względny [%]'])
    merged_df = merged_df.join(tsm_benchmark_df['TSM: błąd średni względny [%]'])
    merged_df = merged_df.round(
        {'SA: czas [ms]': 2, 'TSL: czas [ms]': 2, 'TSM: czas [ms]': 2, 'SA: błąd średni względny [%]': 2,
         'TSL: błąd średni względny [%]': 2, 'TSM: błąd średni względny [%]': 2})

    merged_df.to_csv('data/benchmarks/merged_benchmarks.csv', index=False, float_format='%.2f')


# Script #
# Simulated annealing
# scatter_plot_parameter_analysis(read_csv_to_data_frame('data/simulated_annealing/epoch_iterations_number.csv'),
#                                 xlabel="Liczba iteracji dla stałej temperatury")
# scatter_plot_parameter_analysis(read_csv_to_data_frame('data/simulated_annealing/geometric_cooling_scheme.csv'),
#                                 xlabel="Parametr geometrycznego schematu chłodzenia")
# scatter_plot_parameter_analysis(read_csv_to_data_frame('data/simulated_annealing/initial_temperature.csv'),
#                                 xlabel="Temperatura początkowa")
# scatter_plot_parameter_analysis(read_csv_to_data_frame('data/simulated_annealing/iterations_number.csv'),
#                                 xlabel="Liczba iteracji")
# scatter_plot_parameter_analysis(read_csv_to_data_frame('data/simulated_annealing/linear_cooling_scheme.csv'),
#                                 xlabel="Parametr liniowego schematu chłodzenia")
# scatter_plot_parameter_analysis(read_csv_to_data_frame('data/simulated_annealing/logarithmic_cooling_scheme.csv'),
#                                 xlabel="Parametr logarytmicznego schematu chłodzenia")

# Tabu search
# scatter_plot_parameter_analysis(read_csv_to_data_frame('data/tabu_search_list/cadenza_length_parameter.csv'),
#                                 xlabel="Parametr długości kadencji", size_param=0.8, legend_loc='center right')
# scatter_plot_parameter_analysis(read_csv_to_data_frame('data/tabu_search_list/iterations_number.csv'),
#                                 xlabel="Liczba iteracji")
# scatter_plot_parameter_analysis(
#     read_csv_to_data_frame('data/tabu_search_list/iterations_without_improvement_to_restart.csv'),
#     xlabel="Liczba iteracji bez poprawy wyniku do restartu", size_param=0.8)
# scatter_plot_parameter_analysis(read_csv_to_data_frame('data/tabu_search_list/patterns_number_to_cache.csv'),
#                                 xlabel="Ograniczenie przechowywanych w pamięci punktów przestrzeni", size_param=0.7)
# scatter_plot_parameter_analysis(read_csv_to_data_frame('data/tabu_search_list/tabu_list_size.csv'),
#                                 xlabel="Długość listy tabu", size_param=0.8)

# benchmark_dfs = (
#     {'df': read_csv_to_data_frame('data/benchmarks/simulated_annealing_benchmark.csv'),
#      'label': 'Symulowane wyżarzanie', 'style': 'ro-'},
#     {'df': read_csv_to_data_frame('data/benchmarks/tabu_search_list_benchmark.csv'),
#      'label': "Poszukiwanie z zakazami - lista tabu", 'style': 'gs-'},
#     {'df': read_csv_to_data_frame('data/benchmarks/tabu_search_matrix_benchmark.csv'),
#      'label': 'Poszukiwanie z zakazami - macierz tabu', 'style': 'b^-'}
# )
#
# plot_multiple(benchmark_dfs, x_step=10, y_column='Time')
# plot_multiple(benchmark_dfs, x_step=10, y_column='Mean relative error [%]')

export_benchmark_data_to_csv()
