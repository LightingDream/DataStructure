class Glist:

    def __init__(self, tag):
        self.tag = tag          #1: sublist 0 : atom
        self.atom = None
        self.right = None
        self.down = None
        pass

    pass

class Solution:
    def __substr__(self, Str, l, r):
        res = ''
        for i in range(l, r):
            res = res + Str[i]
        return res
        pass
    def __split__(self, Str):
        cnt, pos = 0, 0
        while pos < len(Str) and (Str[pos] != ',' or cnt != 0):
            if Str[pos] == '(':
                cnt += 1
            if Str[pos] == ')':
                cnt -= 1
            pos += 1
        l = ''
        r = ''
        for i in range(len(Str)):
            if i < pos:
                l = l + Str[i]
            if i > pos:
                r = r + Str[i]
        #r = ''
        return l, r

    @classmethod
    def classMethod(cls):
        print 'Class'

    @staticmethod
    def method():
        print 'Static'


    def solve(self, Str):
        l = Glist(1)
        if len(Str) == 1:
            l.tag, l.atom = 0, Str
            return l
        content = self.__substr__(Str, 1, len(Str) - 1)
        if content == '':
            return None
        else:
            p = l
            left, right = self.__split__(content)
            p.down = self.solve(left)
            q = Glist(1)
            if right != '':
                p.right = q
                p = q
            while right != '':
                left, right = self.__split__(right)
                p.down = self.solve(left)
                if right != '':
                    q = Glist(1)
                    p.right = q
                    p = q
            p.right = None
            pass
        pass
        return l


'''
@property
1. private access
2. easy access
3. can't be modified
'''


def Print(self):
    if self is None or self.tag == 0:
        if self is None:
            print '()',
        else:
            print '%s' % self.atom,
        return
    print '(',
    cur = self
    while cur is not None:
        Print(cur.down)
        cur = cur.right
        if cur is not None:
            print ',',
        pass
    print ')',
    pass


def depth(l):
    if l is None or l.tag == 0:
        return 0
    mx = 0
    while l is not None:
        mx = max(mx, depth(l.down))
        l = l.right
    return mx + 1


if __name__ == '__main__':
    l = Solution().solve('(a,(),(b,c))')
    Print(l)
    print
    print(depth(l))
    pass
