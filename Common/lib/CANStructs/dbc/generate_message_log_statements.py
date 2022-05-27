import sys
import cantools

db = cantools.db.load_file(sys.argv[1])

for message in db.messages:
    string = '"' + message.name + ': '
    for signal in message.signals:
        string += signal.name + ' %u, '
    string = string[:-2]
    string += '", '
    for signal in message.signals:
        string += signal.name + ', '
    string = string[:-2]
    print(string)
    print('')
