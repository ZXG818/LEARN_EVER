import urllib.request
import re

def get_link(url,page):
	head = {}
	head['User-Agent'] = 'Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:59.0) Gecko/20100101 Firefox/59.0'

	req = urllib.request.Request(url,headers = head)

	response = urllib.request.urlopen(req)
	data = response.read()
	pat1 = '<div class="MinHeader".+?<ul class="articleV4Page l">'

	result = re.compile(pat1).findall(str(data))
	result = result[0]

	pat2 = 'src="http://(.+?\.jpg)"'
	linklist = re.compile(pat2).findall(result)

	number = 1
	for link in linklist:
		img_link = 'http://' + link
		try:
			response = urllib.request.urlopen(img_link)
			img_name = 'C://Users//pc//Desktop//picture2//' + str(page) +'-'+ str(number) + '.jpg'
			data = response.read()
			with open(img_name,'wb') as f:
				f.write(data)
			number = number + 1
		except:
			pass

if __name__ == '__main__':
	url = 'http://www.27270.com/ent/meinvtupian/2017/236441.html'
	get_link(url,1)

	for i in range(2,18):
		url = 'http://www.27270.com/ent/meinvtupian/2017/236441_' + str(i) + '.html'
		get_link(url,i)

