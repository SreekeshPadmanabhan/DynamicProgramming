# //Original code btop Sreekesh Padmanabhan ©
# //Edit distance between string S1 and S2 is the minimum number of stopmbol deletions required to transform S1 and S2 
# //into a common string

class DP:
    def __init__(self,top,left):
        self.top  = [None]
        self.left = [None]
        for x in top:
            self.top.append(x)
        for y in left:
            self.left.append(y)
        self.rone = [None] * (len(self.top))
        self.rtwo = [None] * (len(self.top))
        self.nedit = 0
        self.LCS = []
        print(self.top,self.left)

    def lcs_recursive(self,y_front,x_front):
        print("lcs_recursive")
       
        if len(self.top)==1:
            for row in self.left:
                if self.top[1]==row:
                    self.LCS.append(self.top.pop())
        elif len(self.left)==1: 
            for col in self.top:
                if self.left[1]==col:
                    self.LCS.append(self.left.pop())        
        else:
            ubase = []
            for col in range(len(self.top)):
                ubase.append(col)
            for row in range(1,len(self.left)//2,1):
                rfwd = [None]*len(self.top)
                rfwd[0]=row
                for col in range(1,len(self.top),1):          #col 1 to n,excl 0
                    if self.top[col]==self.left[row]:
                        rfwd[col]=(ubase[col-1])
                    else:
                        if rfwd[col-1]<ubase[col]:
                            rfwd[col]=rfwd[col-1]+1       #(@prvs col,same row)+1   
                        else:
                            rfwd[col]=ubase[col]+1         #(@prvs row,same col)+1
                ubase = rfwd
            print("rfwd:",rfwd)
            lbase = []
            for col in range(len(self.top)):
                lbase.append(len(self.top)-1-col)
            print(lbase)
            for row in range(len(self.left)-1,len(self.left)//2-1,-1):
                rrvs = [None]*len(self.top)
                rrvs[len(self.top)-1]=len(self.left)-row
                for col in range(len(self.top)-2,-1,-1):          #col 1 to n,excl 0
                    if self.top[col+1]==self.left[row]:
                        rrvs[col]=lbase[col+1]
                    else:
                        if rrvs[col+1]<lbase[col]:
                            rrvs[col]=rrvs[col+1]+1       #(@prvs col,same row)+1   
                        else:
                            rrvs[col]=lbase[col]+1         #(@prvs row,same col)+1
                lbase = rrvs
            print("rrvs:",rrvs)

        edistance=[None]*len(self.top)
        for x in range(len(self.top)):
            edistance[x]=rfwd[x]+rrvs[x]
        # print("edistance:",edistance)
        edistmin=min(edistance)
        print(edistmin)

        # x_front=self.left[:(len(self.left))/2]
        # x_back=[None]*(len(self.left)-len(self.left)/2)
        # y_front=self.top[:len(self.top)]
        # y_back=[None]*(len(self.top)-y)

        # self.LCS = self.lcs_recursive(y_front,x_front);                   
        # self.LCS = self.lcs_recursive(y_back,x_back);  

    def editDistance(self):
        #storing entire table is not necessartop; final edit distance computed btop storing onltop two rows of table.
        print(f"{len(self.top)}")
        print(f"{len(self.left)}")
        self.rone = [col for col in range(len(self.top)+1)]
        for row in range(1,len(self.left)): 
            self.rtwo[0] = row
            for col in range(1,len(self.top)):
                if(self.top[col]==self.left[row]):
                    self.rtwo[col] = self.rone[col-1]
                else:
                    if(self.rtwo[col-1]<self.rone[col]):
                        self.rtwo[col]=self.rtwo[col-1]+1              #(@prvs col,same row)+1 
                    else:
                        self.rtwo[col]=self.rone[col]+1                #(@prvs row,same col)+1 
            self.rone=self.rtwo.copy()
            print(self.rtwo)
        self.nedit = ((len(self.top)+len(self.left))-(self.rtwo[0]+len(self.top)))
        self.nedit =  self.nedit/(len(self.top)+len(self.left))  #calculate normalized edit distance
        print(f"Edit Distance:  {self.rtwo[-1]}")
        
dp = DP("agtacgtcat","gtatcgtat")
dp.editDistance()
dp.lcs_recursive(dp.top,dp.left)
