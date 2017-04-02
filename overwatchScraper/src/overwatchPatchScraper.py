from bs4 import BeautifulSoup
from urllib import urlopen

file = open("patchnotes.txt", "w");

for page in range(1, 7):
    url = "https://playoverwatch.com/en-us/game/patch-notes/pc/?page=" + str(page)
    page = urlopen(url)

    soup = BeautifulSoup(page, "html.parser")

    def dateHandling (date):
        sept13 = date
        sept13 = sept13[-20:]
        if sept13.strip() == ("September 13th, 2016").strip():
            return ("[2016/9/13]\n").encode('utf-8')
        fixedDate = ""
        date = date[24:]
        fixedDate = fixedDate + "[" + date[-4:] + "/"
        date = date.replace(date[-4:], "")
        dates = {
                'jan': '01',
                'feb': '02',
                'mar': '03',
                'apr': '04', 
                'may': '05',
                'jun': '06',
                'jul': '07',
                'aug': '08',
                'sep': '09', 
                'oct': '10',
                'nov': '11',
                'dec': '12'
                }
        dateStr = date.strip()[:3].lower()
        fixedDate = fixedDate + dates[dateStr] + "/"
        date = date[:-2]
        date = date[-2:]
        intDate = int(date)
        if intDate < 10:
            date = date[-1:]
            fixedDate = fixedDate + "0" + date + "]"
        else:
            fixedDate = fixedDate + date + "]\n"

        return fixedDate
    def listHandling (info, count):
        whitespace = "\r\n\t"
        for bullet in info.find_all("li", recursive = False):
            bulletText = bullet.get_text()
            flag = False
            for nestedList in bullet.find_all("ul", recursive = False):
                nestedText = nestedList.get_text()
                bulletText = bulletText.replace(nestedText,'')
                file.write(("-" * count + bulletText.strip(whitespace) + "\n").encode('utf-8'))
                newcount = count + 1
                listHandling(nestedList, newcount)
                flag = True
            if flag == False:
                file.write(("-" * count + bulletText.strip(whitespace) + "\n").encode('utf-8'))

    for patch in soup.find_all("div", attrs={"class":"patch-notes-body"}):
        date = patch.find("h1")
        dateString = date.get_text()
        file.write((dateHandling(dateString)))
        for info in patch.find_all(["h2","p", "ul"], recursive = False):
            count = 1
            if info.name == "ul":
                listHandling(info, count + 1)
            elif info.name == "h2":
                infoString = info.get_text()
                infoString = infoString.encode('utf-8')
                file.write(infoString + "\n")
            else:
                infoString = "-" + info.get_text()
                infoString = infoString.encode('utf-8')
                file.write(infoString + "\n")
