import ROOT as r
mycolors = []
mycolors.append(r.TColor(11005 , 103 / 255. , 0   / 255. , 31  / 255.))
mycolors.append(r.TColor(11004 , 178 / 255. , 24  / 255. , 43  / 255.))
mycolors.append(r.TColor(11003 , 214 / 255. , 96  / 255. , 77  / 255.))
mycolors.append(r.TColor(11002 , 244 / 255. , 165 / 255. , 130 / 255.))
mycolors.append(r.TColor(11001 , 253 / 255. , 219 / 255. , 199 / 255.))
mycolors.append(r.TColor(11000 , 247 / 255. , 247 / 255. , 247 / 255.))
mycolors.append(r.TColor(11011 , 209 / 255. , 229 / 255. , 240 / 255.))
mycolors.append(r.TColor(11012 , 146 / 255. , 197 / 255. , 222 / 255.))
mycolors.append(r.TColor(11013 , 67  / 255. , 147 / 255. , 195 / 255.))
mycolors.append(r.TColor(11014 , 33  / 255. , 102 / 255. , 172 / 255.))
mycolors.append(r.TColor(11015 , 5   / 255. , 48  / 255. , 97  / 255.))

mycolors.append(r.TColor(3001 , 239 / 255. , 138 / 255. , 98  / 255.))
mycolors.append(r.TColor(3000 , 247 / 255. , 247 / 255. , 247 / 255.))
mycolors.append(r.TColor(3011 , 103 / 255. , 169 / 255. , 207 / 255.))

mycolors.append(r.TColor(5001 , 251 / 255. , 180 / 255. , 174 / 255.))
mycolors.append(r.TColor(5002 , 179 / 255. , 205 / 255. , 227 / 255.))
mycolors.append(r.TColor(5003 , 204 / 255. , 235 / 255. , 197 / 255.))
mycolors.append(r.TColor(5004 , 222 / 255. , 203 / 255. , 228 / 255.))
mycolors.append(r.TColor(5005 , 254 / 255. , 217 / 255. , 166 / 255.))

mycolors.append(r.TColor(7000 ,   0/255. ,   0/255. ,   0/255.))
mycolors.append(r.TColor(7001 , 213/255. ,  94/255. ,   0/255.)) #r
mycolors.append(r.TColor(7002 , 230/255. , 159/255. ,   0/255.)) #o
mycolors.append(r.TColor(7003 , 240/255. , 228/255. ,  66/255.)) #y
mycolors.append(r.TColor(7004 ,   0/255. , 158/255. , 115/255.)) #g
mycolors.append(r.TColor(7005 ,   0/255. , 114/255. , 178/255.)) #b
mycolors.append(r.TColor(7006 ,  86/255. , 180/255. , 233/255.)) #k
mycolors.append(r.TColor(7007 , 204/255. , 121/255. , 167/255.)) #p
mycolors.append(r.TColor(7011 , 110/255. ,  54/255. ,   0/255.)) #alt r
mycolors.append(r.TColor(7012 , 161/255. , 117/255. ,   0/255.)) #alt o
mycolors.append(r.TColor(7013 , 163/255. , 155/255. ,  47/255.)) #alt y
mycolors.append(r.TColor(7014 ,   0/255. , 102/255. ,  79/255.)) #alt g
mycolors.append(r.TColor(7015 ,   0/255. ,  93/255. , 135/255.)) #alt b
mycolors.append(r.TColor(7016 , 153/255. , 153/255. , 153/255.)) #alt k
mycolors.append(r.TColor(7017 , 140/255. ,  93/255. , 119/255.)) #alt p

mycolors.append(r.TColor(9001 ,  60/255. , 186/255. ,  84/255.))
mycolors.append(r.TColor(9002 , 244/255. , 194/255. ,  13/255.))
mycolors.append(r.TColor(9003 , 219/255. ,  50/255. ,  54/255.))
mycolors.append(r.TColor(9004 ,  72/255. , 133/255. , 237/255.))

# Color schemes from Hannsjoerg for WWW analysis
mycolors.append(r.TColor(2001 , 91  / 255. , 187 / 255. , 241 / 255.)) #light-blue
mycolors.append(r.TColor(2002 , 60  / 255. , 144 / 255. , 196 / 255.)) #blue
mycolors.append(r.TColor(2003 , 230 / 255. , 159 / 255. , 0   / 255.)) #orange
mycolors.append(r.TColor(2004 , 180 / 255. , 117 / 255. , 0   / 255.)) #brown
mycolors.append(r.TColor(2005 , 245 / 255. , 236 / 255. , 69  / 255.)) #yellow
mycolors.append(r.TColor(2006 , 215 / 255. , 200 / 255. , 0   / 255.)) #dark yellow
mycolors.append(r.TColor(2007 , 70  / 255. , 109 / 255. , 171 / 255.)) #blue-violet
mycolors.append(r.TColor(2008 , 70  / 255. , 90  / 255. , 134 / 255.)) #violet
mycolors.append(r.TColor(2009 , 55  / 255. , 65  / 255. , 100 / 255.)) #dark violet
mycolors.append(r.TColor(2010 , 120 / 255. , 160 / 255. , 0   / 255.)) #light green
mycolors.append(r.TColor(2011 , 0   / 255. , 158 / 255. , 115 / 255.)) #green
mycolors.append(r.TColor(2012 , 204 / 255. , 121 / 255. , 167 / 255.)) #pink?

default_colors = []
default_colors.append(2005)
default_colors.append(2001)
default_colors.append(2003)
default_colors.append(2007)
default_colors.append(920)
default_colors.extend(range(2001, 2013))
default_colors.extend(range(7001, 7018))

