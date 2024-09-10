import numpy as np
import matplotlib.pyplot as plt


def game():
    return np.random.randint(1, 9)


def game_results():
    finalvalue = np.zeros(100)
    finalroll = np.zeros(100)
    for i in range(100):
        finalvalue[i] = game() + game()
        finalroll[i] = i + 1
    return finalvalue, finalroll


def graph(finalvalue, finalroll):
    plt.figure(1, tight_layout=True)
    
    plt.subplot(2, 2, 1)
    plt.suptitle("Scatter, Line, Histogram, and Pie Plot")
    plt.pie([np.count_nonzero(finalvalue == i) for i in range(1, 15)],
            labels=[str(i) for i in range(1, 15)])
    plt.xlabel("Dice Sums")
    plt.ylabel("Frequency")

    plt.subplot(2, 2, 2)
    plt.plot(finalroll, finalvalue)
    plt.xlabel("Trials")
    plt.ylabel("Dice Sums")

    plt.subplot(2, 2, 3)
    plt.scatter(finalroll, finalvalue)
    plt.xlabel("Trials")
    plt.ylabel("Dice Sums")
    plt.subplot(2, 2, 4)
    plt.hist(finalvalue, bins=4)

    plt.show()
if __name__ == "__main__":
    finalvalue, finalroll = game_results()
    graph(finalvalue, finalroll)