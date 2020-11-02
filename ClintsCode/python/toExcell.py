import csv


def readFile(data):
    file = open('../results/bigFile.txt', 'r')
    lines = file.readlines()
    data = []
    for x in lines:
        data.append(x)

    return data


excel = []
excel = readFile(excel)

print(excel)