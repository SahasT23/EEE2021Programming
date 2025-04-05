import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns

def plot_factorial_performance(csv_path):
    # Read the results data
    try:
        df = pd.read_csv(csv_path)
    except FileNotFoundError:
        print(f"Error: File {csv_path} not found!")
        return

    # Set up plotting style
    sns.set(style="whitegrid")
    plt.figure(figsize=(12, 6))

    # Create a line plot for each method
    methods = df['Method'].unique()
    
    # Regular linear plot
    plt.subplot(1, 2, 1)
    for method in methods:
        method_data = df[df['Method'] == method]
        plt.plot(method_data['Input'], method_data['ExecutionTime(s)'], 
                marker='o', label=method)
    
    plt.title("Factorial Algorithm Performance")
    plt.xlabel("Input Size (n)")
    plt.ylabel("Execution Time (seconds)")
    plt.legend()
    
    # Log-log plot to show complexity differences
    plt.subplot(1, 2, 2)
    for method in methods:
        method_data = df[df['Method'] == method]
        plt.loglog(method_data['Input'], method_data['ExecutionTime(s)'], 
                  marker='o', label=method)
    
    plt.title("Log-Log Performance Comparison")
    plt.xlabel("Input Size (n)")
    plt.ylabel("Execution Time (seconds)")
    plt.legend()

    plt.tight_layout()
    
    # Save and show plot
    plt.savefig("factorial_performance.png")
    plt.show()
    
    print("Performance plot saved as factorial_performance.png")

if __name__ == "__main__":
    csv_file = "factorial_results.csv"
    plot_factorial_performance(csv_file)