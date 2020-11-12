import csv


def readFile():
    file = open('../results/bigFile.txt', 'r')
    lines = file.readlines()
    string =""
    data = []
    with open('data.csv', 'w') as csvfile:
        writer = csv.writer(csvfile)

        for x in lines:
            #print("line: ")
            for y in x:
                if y != ' ' and y !='\n':
                    string += y
                else:
                    data.append(string)    
                    string =""
            
            #print(string)
            #data.append(string)
            print(data)
            string = ""
            writer.writerow(data)
            data.clear()



readFile()

#print(excel)