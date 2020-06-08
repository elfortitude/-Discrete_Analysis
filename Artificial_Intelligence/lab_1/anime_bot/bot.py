#!/usr/bin/env python3

import constant as const
import Naruto
import specifications_per as spec_per
import telebot
from telebot import types
from telebot.types import Message

# from telebot import apihelper
#
# apihelper.proxy = {'https': 'socks5h://248438751:5TspWLZ1@orbtl.s5.opennetwork.cc:999'}

TOKEN = const.TOKEN

bot = telebot.TeleBot(TOKEN)

list_of_spec = []
unknown_person = Naruto.Naruto_Find(spec_per.person)
count = 0
characteristic = ""
persons = []

@bot.message_handler(commands=['start'])
def say_hi(message):
    bot.send_message(message.chat.id, const.hello_answer)
    global list_of_spec
    global persons
    global count
    count = 0
    persons = spec_per.names
    list_of_spec = list(spec_per.person.keys())
    del list_of_spec[0]
    keyboard_func(message)

def keyboard_func(message):
    markup = types.ReplyKeyboardMarkup(resize_keyboard=True)
    for item in list_of_spec:
        markup.add(item)
    bot.send_message(message.chat.id, "Выбери:", reply_markup=markup)

@bot.message_handler(commands=['help'])
def help_me(message):
    bot.send_message(message.chat.id, const.help_answer)

@bot.message_handler(content_types=['text'])
def echo_digits(message: Message):
    global list_of_spec
    global characteristic
    global count
    global unknown_person
    global persons
    i = 0
    if count == 0 and message.text in list_of_spec:
        count += 1
        characteristic = message.text
        if message.text == 'homeland':
            list_of_spec = spec_per.homeland.copy()
            keyboard_func(message)
        elif message.text == 'rang':
            list_of_spec = spec_per.rang.copy()
            keyboard_func(message)
        elif message.text == 'specialization':
            list_of_spec = spec_per.specialization.copy()
            keyboard_func(message)
        elif message.text == 'element':
            list_of_spec = spec_per.element.copy()
            keyboard_func(message)
        elif message.text == 'team':
            list_of_spec = spec_per.team.copy()
            keyboard_func(message)
        elif message.text == 'gender':
            list_of_spec = spec_per.gender.copy()
            keyboard_func(message)
        elif message.text == 'age_more_20years':
            list_of_spec = spec_per.age_more_20years.copy()
            keyboard_func(message)
        elif message.text == 'shogi':
            list_of_spec = spec_per.shogi.copy()
            keyboard_func(message)
        elif message.text == 'hakage':
            list_of_spec = spec_per.hakage.copy()
            keyboard_func(message)
        elif message.text == 'sharingan':
            list_of_spec = spec_per.sharingan.copy()
            keyboard_func(message)
        elif message.text == 'sarutobi':
            list_of_spec = spec_per.sarutobi.copy()
            keyboard_func(message)
        elif message.text == 'dzinchuriki':
            list_of_spec = spec_per.dzinchuriki.copy()
            keyboard_func(message)
        elif message.text == 'byakugan':
            list_of_spec = spec_per.byakugan.copy()
            keyboard_func(message)
    elif count == 1:
        count -= 1
        unknown_person.dictionary[characteristic] = message.text
        persons = unknown_person.find(persons, characteristic)
        if len(persons) == 1:
            bot.send_message(message.chat.id, const.finish_answer1)
            bot.send_message(message.chat.id, persons[0].dictionary['name'])
            bot.send_message(message.chat.id, const.finish_answer2)
            list_of_spec = ['/start']
            keyboard_func(message)
        elif len(persons) == 0:
            bot.send_message(message.chat.id, const.error_answer)
            list_of_spec = ['/start']
            keyboard_func(message)
        else:
            list_of_spec = unknown_person.comparing(persons)
            keyboard_func(message)
    else:
        bot.reply_to(message, const.other_answer)

bot.polling(none_stop=True)
