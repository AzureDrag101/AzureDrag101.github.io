#Author:Kosy Okafor
#Class:CSCI 1170-02
#Date:November 23,2022
#This program validates emails within text files
def main():
        
    filename = input("Enter file: ")
    email_file = open(filename, 'r')
    outFilename = input("Enter output file: ")
    outfile = open(outFilename, 'w')
    count = 0
    line = email_file.readline()
    while line != '':
        line = line.rstrip('\n')
        email = line.split()
        for ch in email:
            ch = ch.strip(',')
            ch= ch.strip('>')
            ch = ch.strip('<')
            for i in ch:
                position = ch.find('@')
                    
            if position != -1:    
                username = ch[0:position]
                domain = ch[position+1:len(ch)]
               
                if validDomain(domain) and validUsername(username) == True:
                    outfile.write(ch + '\n')
                    
                    count += 1
        line = email_file.readline()
    print(f'You have found {count} valid emails')
    email_file.close()
def validDomain(domain):
    check = False
    for ch in domain:
        
        if domain[0] == '.' or domain[-1] == '.':
            check = False
        elif '..' in domain:
            check = False
        elif domain.find('.') == -1:
            check = False
        elif '@' in domain:
            check = False
        elif '_' in domain:
            check = False
        else:
            if ch.isalnum():
                check = True
            elif ch == '.' or ch == '-':
                check = True
            else:
                check = False
            
    return check
def validUsername(username):
    check = False
    for ch in username:
        
        if username.isalnum():
            check = True
        if ch == '.' or ch == '-' or ch == '_':
            check = True
    return check
        
    
main()

