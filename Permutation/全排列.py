ans = []
def swap(s, a, b):
    tmp = s[b];
    s[b] = s[a]
    s[a] = tmp

def perm(s, index, size):
    if index >= size:
        #print(s)
        ans.append(s.copy()) 
    else:
        for i in range(index, size):
            swap(s, i, index)
            perm(s, index + 1, size)
            swap(s, i, index)


s = input()
l = list(s)
perm(l, 0, len(l))
print(ans)
