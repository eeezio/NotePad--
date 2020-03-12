from selenium import webdriver
from selenium.webdriver.common.keys import Keys


def hello(string):
    browser = webdriver.Edge()
    browser.get('https://www.baidu.com')
    input = browser.find_element_by_id("kw")
    input.send_keys(string)
    input.send_keys(Keys.ENTER)
    while True:
        if browser.current_url == None:
            break
