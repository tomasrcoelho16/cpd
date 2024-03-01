import time

def OnMult(m_ar):
    pha = [1] * m_ar * m_ar
    phb = [1] * m_ar * m_ar
    phc = [0] * m_ar * m_ar

    Time1 = time.time()
    for i in range(m_ar):
        for j in range(m_ar):
            phb[i*m_ar + j] = i + 1

    for i in range(m_ar):
        for j in range(m_ar):
            temp = 0
            for k in range(m_ar):
                temp += pha[i*m_ar + k] * phb[k*m_ar + j]
            phc[i*m_ar + j] = temp
    
    Time2 = time.time()
    print("Time: " + str(Time2-Time1) + " seconds")     

    print("Result matrix: s")
    for i in range(min(m_ar,10)):
        print(phc[i], end =" ")
    print()



def OnMultLine(m_ar):
    pha = [1] * m_ar * m_ar
    phb = [1] * m_ar * m_ar
    phc = [0] * m_ar * m_ar

    Time1 = time.time()
    for i in range(m_ar):
        for j in range(m_ar):
            phb[i*m_ar + j] = i + 1

    for i in range(m_ar):
        for j in range(m_ar):
            for k in range(m_ar):
                phc[i*m_ar + j] += pha[i*m_ar + k] * phb[k*m_ar + j]
    
    Time2 = time.time()
    print("Time: " + str(Time2-Time1) + " seconds")              

    print("Result matrix: ")
    for i in range(min(m_ar,10)):
        print(phc[i], end =" ")
    print()



def main():
    while(True):
        print("1. Multiplication")
        print("2. Line Multiplication")
        c = input("Selection?:")
        if c != str(1) and c != str(2):
            continue
        else:
            m_ar = input("Dimensions: lins=cols ? ")
            if c == str(1):
                OnMult(int(m_ar))
            if c == str(2):
                OnMultLine(int(m_ar))
main()