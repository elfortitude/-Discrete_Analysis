#!/usr/bin/env python3

import Naruto as naruto


person = {
    'name' : None,
    'homeland' : None,
    'gender' : None,
    'specialization' : None,
    'rang' : None,
    'age_more_20years' : None,
    'hero' : None,
    'shogi' : None,
    'hakage' : None,
    'sharingan' : None,
    'sarutobi' : None,
    'dzinchuriki' : None,
    'element' : None,
    'team' : None,
    'byakugan' : None
    }    

translate = {
    'name' : 'Имя',
    'homeland' : 'Деревня',
    'gender' : 'Пол',
    'specialization' : 'Специализация',
    'rang' : 'Звание',
    'age_more_20years' : 'Больше ли 20?',
    'hero' : 'Положительный ли персонаж?',
    'shogi' : 'Играет ли в шоги?',
    'hakage' : 'Был или является хокаге?',
    'sharingan' : 'Шаринган',
    'sarutobi' : 'Сарутоби',
    'dzinchuriki' : 'Джинчурики',
    'element' : 'Основной элемент',
    'team' : 'Команда',
    'byakugan' : 'Бьякуган'
}

name = ['Naruto', 'Saske', 'Sakura', 'Kakashi','Shukomaru','Ino', 'Chodzi','Asyma','Gaara','Kankyro','Temary','Tenten','Rock Li',
         'Nedzi','Gay','Xoshirama','Tobirama','Xiruzen','Minato','Tsunada','Sasori','Daydara','Itachi','Kisame','Xidan','Kakuzu',
          'Pain','Konan','Tobi','Orochimaru','Zetsu','Xinata','Kiba','Shino']
rang = ['Genin','Chunin','Johnin','Kage', 'None']
homeland = ['List', 'Sand', 'Rain', 'Waterfall', 'Fog', 'None', 'Stone']
specialization = ['Heal','Ninjutsu','Taijutsu','Genjutsu', 'Puppets']
element = ['Wind','Earth','Fire','Lightning','Water', 'Tree', 'All', 'None']
team = ['7', 'InoShukoCho', '3', 'Akutsuke', 'None', 'Sand']
gender = ['Male', 'Female']
age_more_20years = ['Yes', 'No']
hero = ['Yes', 'No']
shogi = ['Yes', 'No']
hakage = ['Yes', 'No']
sharingan = ['Yes', 'No']
sarutobi = ['Yes', 'No']
dzinchuriki = ['Yes', 'No']
byakugan = ['Yes', 'No']

Naruto = {
    'name' : 'Naruto',
    'homeland' : 'List',
    'gender' : 'Male',
    'specialization' : 'Ninjutsu',
    'rang' : 'Genin',
    'age_more_20years' : 'No',
    'hero' : 'Yes',
    'shogi' : 'No',
    'hakage' : 'Yes',
    'sharingan' : 'No',
    'sarutobi' : 'No',
    'dzinchuriki' : 'Yes',
    'element' : 'Wind',
    'team' : '7',
    'byakugan' : 'No'
    }    

Saske = {
    'name' : 'Saske',
    'homeland' : 'List',
    'gender' : 'Male',
    'specialization' : 'Ninjutsu',
    'rang' : 'Genin',
    'age_more_20years' : 'No',
    'hero' : 'Yes',
    'shogi' : 'No',
    'hakage' : 'No',
    'sharingan' : 'Yes',
    'sarutobi' : 'No',
    'dzinchuriki' : 'No',
    'element' : 'Fire',
    'team' : '7',
    'byakugan' : 'No'
    }

Kakashi = {
    'name' : 'Kakashi',
    'homeland' : 'List',
    'gender' : 'Male',
    'specialization' : 'Ninjutsu',
    'rang' : 'Johnin',
    'age_more_20years' : 'Yes',
    'hero' : 'Yes',
    'shogi' : 'No',
    'hakage' : 'Yes',
    'sharingan' : 'Yes',
    'sarutobi' : 'No',
    'dzinchuriki' : 'No',
    'element' : 'All',
    'team' : '7',
    'byakugan' : 'No'
    }

Shukomaru = {
    'name' : 'Shukomaru',
    'homeland' : 'List',
    'gender' : 'Male',
    'specialization' : 'Ninjutsu',
    'rang' : 'Chunin',
    'age_more_20years' : 'No',
    'hero' : 'Yes',
    'shogi' : 'Yes',
    'hakage' : 'No',
    'sharingan' : 'No',
    'sarutobi' : 'No',
    'dzinchuriki' : 'No',
    'element' : 'None',
    'team' : 'InoShukoCho',
    'byakugan' : 'No'
    }

Sakura = {
    'name' : 'Sakura',
    'homeland' : 'List',
    'gender' : 'Female',
    'specialization' : 'Heal',
    'rang' : 'Chunin',
    'age_more_20years' : 'No',
    'hero' : 'Yes',
    'shogi' : 'No',
    'hakage' : 'No',
    'sharingan' : 'No',
    'sarutobi' : 'No',
    'dzinchuriki' : 'No',
    'element' : None,
    'team' : '7',
    'byakugan' : 'No'
    }

Ino = {
    'name' : 'Ino',
    'homeland' : 'List',
    'gender' : 'Female',
    'specialization' : 'Ninjutsu',
    'rang' : 'Chunin',
    'age_more_20years' : 'No',
    'hero' : 'Yes',
    'shogi' : 'No',
    'hakage' : 'No',
    'sharingan' : 'No',
    'sarutobi' : 'No',
    'dzinchuriki' : 'No',
    'element' : 'Earth',
    'team' : 'InoShukoCho',
    'byakugan' : 'No'
    }

Chodzi = {
    'name' : 'Chodzi',
    'homeland' : 'List',
    'gender' : 'Male',
    'specialization' : 'Ninjutsu',
    'rang' : 'Chunin',
    'age_more_20years' : 'No',
    'hero' : 'Yes',
    'shogi' : 'No',
    'hakage' : 'No',
    'sharingan' : 'No',
    'sarutobi' : 'No',
    'dzinchuriki' : 'No',
    'element' : 'Earth',
    'team' : 'InoShukoChio',
    'byakugan' : 'No'
    }  

Asuma = {
    'name' : 'Asuma',
    'homeland' : 'List',
    'gender' : 'Male',
    'specialization' : 'Ninjutsu',
    'rang' : 'Johnin',
    'age_more_20years' : 'Yes',
    'hero' : 'Yes',
    'shogi' : 'Yes',
    'hakage' : 'No',
    'sharingan' : 'No',
    'sarutobi' : 'No',
    'dzinchuriki' : 'No',
    'element' : 'Wind',
    'team' : 'InoShukoCho',
    'byakugan' : 'No'
    }   

Gaara = {
    'name' : 'Gaara',
    'homeland' : 'Sand',
    'gender' : 'Male',
    'specialization' : 'Ninjutsu',
    'rang' : 'Chunin',
    'age_more_20years' : 'No',
    'hero' : 'Yes',
    'shogi' : 'No',
    'hakage' : 'No',
    'sharingan' : 'No',
    'sarutobi' : 'No',
    'dzinchuriki' : 'Yes',
    'element' : 'Earth',
    'team' : 'Sand',
    'byakugan' : 'No'
    }   

Kankyro = {
    'name' : 'Kankyro',
    'homeland' : 'Sand',
    'gender' : 'Male',
    'specialization' : 'Puppets',
    'rang' : 'Chunin',
    'age_more_20years' : 'No',
    'hero' : 'Yes',
    'shogi' : 'No',
    'hakage' : 'No',
    'sharingan' : 'No',
    'sarutobi' : 'No',
    'dzinchuriki' : 'No',
    'element' : 'Wind',
    'team' : 'Sand',
    'byakugan' : 'No'
    }   

Temary = {
    'name' : 'Temary',
    'homeland' : 'Sand',
    'gender' : 'Female',
    'specialization' : 'Ninjutsu',
    'rang' : 'Chunin',
    'age_more_20years' : 'No',
    'hero' : 'Yes',
    'shogi' : 'No',
    'hakage' : 'No',
    'sharingan' : 'No',
    'sarutobi' : 'No',
    'dzinchuriki' : 'No',
    'element' : 'Wind',
    'team' : 'InoShukoCho',
    'byakugan' : 'No'
    }   
    
Tenten = {
    'name' : 'Tenten',
    'homeland' : 'List',
    'gender' : 'Female',
    'specialization' : 'Taijutsu',
    'rang' : 'Chunin',
    'age_more_20years' : 'No',
    'hero' : 'Yes',
    'shogi' : 'No',
    'hakage' : 'No',
    'sharingan' : 'No',
    'sarutobi' : 'No',
    'dzinchuriki' : 'No',
    'element' : None,
    'team' : '3',
    'byakugan' : 'No'
    }   
    
Rock_Li = {
    'name' : 'Rock_Li',
    'homeland' : 'List',
    'gender' : 'Male',
    'specialization' : 'Taijutsu',
    'rang' : 'Chunin',
    'age_more_20years' : 'No',
    'hero' : 'Yes',
    'shogi' : 'No',
    'hakage' : 'No',
    'sharingan' : 'No',
    'sarutobi' : 'No',
    'dzinchuriki' : 'No',
    'element' : None,
    'team' : '3',
    'byakugan' : 'No'
    }

Asyma = {
    'name' : 'Asyma',
    'homeland' : 'List',
    'gender' : 'Male',
    'specialization' : 'Ninjutsu',
    'rang' : 'Johnin',
    'age_more_20years' : 'Yes',
    'hero' : 'Yes',
    'shogi' : 'Yes',
    'hakage' : 'No',
    'sharingan' : 'No',
    'sarutobi' : 'Yes',
    'dzinchuriki' : 'No',
    'element' : 'Wind',
    'team' : 'InoShukoChio',
    'byakugan' : 'No'
    }  

Nedzi = {
    'name' : 'Nedzi',
    'homeland' : 'List',
    'gender' : 'Male',
    'specialization' : 'Taijutsu',
    'rang' : 'Chunin',
    'age_more_20years' : 'No',
    'hero' : 'Yes',
    'shogi' : 'No',
    'hakage' : 'No',
    'sharingan' : 'No',
    'sarutobi' : 'No',
    'dzinchuriki' : 'No',
    'element' : 'Earth',
    'team' : '3',
    'byakugan' : 'Yes'
    }  
    
Gay = {
    'name' : 'Gay',
    'homeland' : 'List',
    'gender' : 'Male',
    'specialization' : 'Taijutsu',
    'rang' : 'Johnin',
    'age_more_20years' : 'Yes',
    'hero' : 'Yes',
    'shogi' : 'No',
    'hakage' : 'No',
    'sharingan' : 'No',
    'sarutobi' : 'No',
    'dzinchuriki' : 'No',
    'element' : None,
    'team' : '3',
    'byakugan' : 'Yes'
    }  

Xoshirama = {
    'name' : 'Xoshirama',
    'homeland' : 'List',
    'gender' : 'Male',
    'specialization' : 'Ninjutsu',
    'rang' : 'Kage',
    'age_more_20years' : 'Yes',
    'hero' : 'Yes',
    'shogi' : 'No',
    'hakage' : 'Yes',
    'sharingan' : 'No',
    'sarutobi' : 'No',
    'dzinchuriki' : 'No',
    'element' : 'Tree',
    'team' : None,
    'byakugan' : 'Yes'
    }  
    
Tobirama = {
    'name' : 'Tobirama',
    'homeland' : 'List',
    'gender' : 'Male',
    'specialization' : 'Ninjutsu',
    'rang' : 'Kage',
    'age_more_20years' : 'Yes',
    'hero' : 'Yes',
    'shogi' : 'No',
    'hakage' : 'Yes',
    'sharingan' : 'No',
    'sarutobi' : 'No',
    'dzinchuriki' : 'No',
    'element' : 'All',
    'team' : None,
    'byakugan' : 'No'
    }  

Xiruzen = {
    'name' : 'Xiruzen',
    'homeland' : 'List',
    'gender' : 'Male',
    'specialization' : 'Ninjutsu',
    'rang' : 'Kage',
    'age_more_20years' : 'Yes',
    'hero' : 'Yes',
    'shogi' : 'Yes',
    'hakage' : 'Yes',
    'sharingan' : 'No',
    'sarutobi' : 'Yes',
    'dzinchuriki' : 'No',
    'element' : 'All',
    'team' : 'All',
    'byakugan' : 'No'
    }  

Minato = {
    'name' : 'Minato',
    'homeland' : 'List',
    'gender' : 'Male',
    'specialization' : 'Ninjutsu',
    'rang' : 'Kage',
    'age_more_20years' : 'Yes',
    'hero' : 'Yes',
    'shogi' : 'No',
    'hakage' : 'Yes',
    'sharingan' : 'No',
    'sarutobi' : 'No',
    'dzinchuriki' : 'Yes',
    'element' : 'Lightning',
    'team' : None,
    'byakugan' : 'No'
    } 
    
Tsunada = {
    'name' : 'Tsunada',
    'homeland' : 'List',
    'gender' : 'Female',
    'specialization' : 'Heal',
    'rang' : 'Kage',
    'age_more_20years' : 'Yes',
    'hero' : 'Yes',
    'shogi' : 'No',
    'hakage' : 'Yes',
    'sharingan' : 'No',
    'sarutobi' : 'No',
    'dzinchuriki' : 'No',
    'element' : 'All',
    'team' : None,
    'byakugan' : 'No'
    }  

Sasori = {
    'name' : 'Sasori',
    'homeland' : 'Sand',
    'gender' : 'Male',
    'specialization' : 'Puppets',
    'rang' : 'Johnin',
    'age_more_20years' : 'Yes',
    'hero' : 'No',
    'shogi' : 'No',
    'hakage' : 'No',
    'sharingan' : 'No',
    'sarutobi' : 'No',
    'dzinchuriki' : 'No',
    'element' : None,
    'team' : 'Akutsuke',
    'byakugan' : 'No'
    }  

Daydara = {
    'name' : 'Daydara',
    'homeland' : 'Stone',
    'gender' : 'Male',
    'specialization' : 'Ninjutsu',
    'rang' : 'Johnin',
    'age_more_20years' : 'No',
    'hero' : 'No',
    'shogi' : 'No',
    'hakage' : 'No',
    'sharingan' : 'No',
    'sarutobi' : 'No',
    'dzinchuriki' : 'No',
    'element' : 'Earth',
    'team' : 'Akutsuke',
    'byakugan' : 'No'
    } 

Itachi = {
    'name' : 'Itachi',
    'homeland' : 'List',
    'gender' : 'Male',
    'specialization' : 'Genjutsu',
    'rang' : 'Johnin',
    'age_more_20years' : 'No',
    'hero' : 'Yes',
    'shogi' : 'No',
    'hakage' : 'No',
    'sharingan' : 'Yes',
    'sarutobi' : 'No',
    'dzinchuriki' : 'No',
    'element' : 'Fire',
    'team' : 'Akutsuke',
    'byakugan' : 'No'
    }
    
Kisame = {
    'name' : 'Kisame',
    'homeland' : 'Fog',
    'gender' : 'Male',
    'specialization' : 'Ninjutsu',
    'rang' : 'Johnin',
    'age_more_20years' : 'Yes',
    'hero' : 'No',
    'shogi' : 'No',
    'hakage' : 'No',
    'sharingan' : 'No',
    'sarutobi' : 'No',
    'dzinchuriki' : 'No',
    'element' : 'Water',
    'team' : 'Akutsuke',
    'byakugan' : 'No'
    }
    
Xidan = {
    'name' : 'Xidan',
    'homeland' : 'Stone',
    'gender' : 'Male',
    'specialization' : 'Taijutsu',
    'rang' : 'Johnin',
    'age_more_20years' : 'Yes',
    'hero' : 'No',
    'shogi' : 'No',
    'hakage' : 'No',
    'sharingan' : 'No',
    'sarutobi' : 'No',
    'dzinchuriki' : 'No',
    'element' : None,
    'team' : 'Akutsuke',
    'byakugan' : 'No'
    }
    
Kakuzu = {
    'name' : 'Kakuzu',
    'homeland' : 'Faterfall',
    'gender' : 'Male',
    'specialization' : 'Ninjutsu',
    'rang' : 'Johnin',
    'age_more_20years' : 'Yes',
    'hero' : 'No',
    'shogi' : 'No',
    'hakage' : 'No',
    'sharingan' : 'No',
    'sarutobi' : 'No',
    'dzinchuriki' : 'No',
    'element' : 'Earth',
    'team' : 'Akutsuke',
    'byakugan' : 'No'
    }

Pain = {
    'name' : 'Pain',
    'homeland' : 'Rain',
    'gender' : 'Male',
    'specialization' : 'Ninjutsu',
    'rang' : 'Johnin',
    'age_more_20years' : 'Yes',
    'hero' : 'No',
    'shogi' : 'No',
    'hakage' : 'No',
    'sharingan' : 'No',
    'sarutobi' : 'No',
    'dzinchuriki' : 'No',
    'element' : 'All',
    'team' : 'Akutsuke',
    'byakugan' : 'No'
    }

Konan = {
    'name' : 'Konan',
    'homeland' : 'Rain',
    'gender' : 'Female',
    'specialization' : 'Ninjutsu',
    'rang' : 'Johnin',
    'age_more_20years' : 'Yes',
    'hero' : 'No',
    'shogi' : 'No',
    'hakage' : 'No',
    'sharingan' : 'No',
    'sarutobi' : 'No',
    'dzinchuriki' : 'No',
    'element' : 'Wind',
    'team' : 'Akutsuke',
    'byakugan' : 'No'
    }

Tobi = {
    'name' : 'Tobi',
    'homeland' : 'List',
    'gender' : 'Male',
    'specialization' : 'Ninjutsu',
    'rang' : 'Johnin',
    'age_more_20years' : 'Yes',
    'hero' : 'No',
    'shogi' : 'No',
    'hakage' : 'No',
    'sharingan' : 'Yes',
    'sarutobi' : 'No',
    'dzinchuriki' : 'No',
    'element' : 'All',
    'team' : 'Akutsuke',
    'byakugan' : 'No'
    }

Zetsu = {
    'name' : 'Zetsu',
    'homeland' : 'None',
    'gender' : 'None',
    'specialization' : 'Ninjutsu',
    'rang' : 'Johnin',
    'age_more_20years' : 'Yes',
    'hero' : 'No',
    'shogi' : 'No',
    'hakage' : 'No',
    'sharingan' : 'No',
    'sarutobi' : 'No',
    'dzinchuriki' : 'No',
    'element' : 'All',
    'team' : 'Akutsuke',
    'byakugan' : 'No'
    }

Orochimaru = {
    'name' : 'Orochimaru',
    'homeland' : 'List',
    'gender' : 'Male',
    'specialization' : 'Ninjutsu',
    'rang' : 'Johnin',
    'age_more_20years' : 'Yes',
    'hero' : 'No',
    'shogi' : 'No',
    'hakage' : 'No',
    'sharingan' : 'No',
    'sarutobi' : 'No',
    'dzinchuriki' : 'No',
    'element' : 'All',
    'team' : None,
    'byakugan' : 'No'
    }

Xinata = {
    'name' : 'Xinata',
    'homeland' : 'List',
    'gender' : 'Female',
    'specialization' : 'Taijutsu',
    'rang' : 'Chunin',
    'age_more_20years' : 'No',
    'hero' : 'Yes',
    'shogi' : 'No',
    'hakage' : 'No',
    'sharingan' : 'No',
    'sarutobi' : 'No',
    'dzinchuriki' : 'No',
    'element' : 'Earth',
    'team' : '8',
    'byakugan' : 'Yes'
    }  

Kiba = {
    'name' : 'Kiba',
    'homeland' : 'List',
    'gender' : 'Male',
    'specialization' : 'Taijutsu',
    'rang' : 'Chunin',
    'age_more_20years' : 'No',
    'hero' : 'Yes',
    'shogi' : 'No',
    'hakage' : 'No',
    'sharingan' : 'No',
    'sarutobi' : 'No',
    'dzinchuriki' : 'No',
    'element' : 'Earth',
    'team' : '8',
    'byakugan' : 'No'
    }

Shino = {
    'name' : 'Shino',
    'homeland' : 'List',
    'gender' : 'Male',
    'specialization' : 'Genjutsu',
    'rang' : 'Chunin',
    'age_more_20years' : 'No',
    'hero' : 'Yes',
    'shogi' : 'No',
    'hakage' : 'No',
    'sharingan' : 'No',
    'sarutobi' : 'No',
    'dzinchuriki' : 'No',
    'element' : 'Fire',
    'team' : '8',
    'byakugan' : 'No'
    }

names = []

name_dict = [Naruto, Saske, Sakura, Kakashi,Shukomaru,Ino, Chodzi,Asyma,Gaara,Kankyro,Temary,Tenten,Rock_Li,
         Nedzi,Gay,Xoshirama,Tobirama,Xiruzen,Minato,Tsunada,Sasori,Daydara,Itachi,Kisame,Xidan,Kakuzu,
          Pain,Konan,Tobi,Orochimaru,Zetsu,Xinata,Kiba,Shino]

for i in range(len(name_dict)):
    names.append(naruto.Naruto_Find(name_dict[i]))
