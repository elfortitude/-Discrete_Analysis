#!/usr/bin/env python3

class Naruto_Find:
    
    def __init__(self, dictionary):
        self.dictionary = dictionary
    def find(self, naruto_all, attribute):
        target = []
        for character in naruto_all:
            if character.dictionary[attribute] == self.dictionary.get(attribute):
                target.append(character)
        return target
    def comparing(self, target):
        actual_attr = []
        a = target[0]
        for key in target[0].dictionary:
            for i in range(len(target)):
                if a.dictionary[key] != target[i].dictionary.get(key):
                    actual_attr.append(key)
                    break
        del actual_attr[0]
        return actual_attr