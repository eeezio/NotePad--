import http.client
import hashlib
import urllib
import random
import json


def hello(q):
    appid = '20200309000395113'  # 填写你的appid
    secretKey = 'hopsKdsqc0vqKH25PFOV'  # 填写你的密钥
    httpClient = None
    myurl = '/api/trans/vip/translate'

    fromLang = 'auto'  #原文语种
    toLang = 'zh'  #译文语种
    salt = random.randint(32768, 65536)
    sign = appid + q + str(salt) + secretKey
    sign = hashlib.md5(sign.encode()).hexdigest()
    myurl = myurl + '?appid=' + appid + '&q=' + urllib.parse.quote(
        q) + '&from=' + fromLang + '&to=' + toLang + '&salt=' + str(
            salt) + '&sign=' + sign
    httpClient = http.client.HTTPConnection('api.fanyi.baidu.com')
    httpClient.request('GET', myurl)
    # response是HTTPResponse对象
    response = httpClient.getresponse()
    result_all = response.read()
    result = json.loads(result_all)
    # print(bytes(result['trans_result'][0]['dst'], encoding='UTF-8'))
    return result['trans_result'][0]['dst']
# hello('USTC')