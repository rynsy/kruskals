def prep_data(n):
    times = []
    with open(str(n), "r") as f:
        for line in f:
                times.append(line.split(":"))
    for i in times:
        i[0] = int(i[0])
        i[1] = int(i[1])
        i[2] = int(i[2])
        i[3] = i[3].rstrip()
        i[3] = float(i[3])
    times.sort(key=lambda x: x[0])
    return times
