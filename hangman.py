# Hangman Game

import random

class Hangman:

	def __init__(self,filename):

		print("  HANGMAN")
		print("You have 10 mistakes to guess the word or you die")
		print("_____________")
		print("|")
		print("|")
		print("|")
		print("|")
		print("|")
		print("|")
		print("|______________|")
		print("|______________|")

		self.filename = filename
		self.count = 0
		self.let_used = []
		self.complete = False

	def PicUpdate(self):

		if self.count == 1:
			print("You have 9 mistakes left to guess the word or you die")
			print("_____________")
			print("|           |")
			print("|")
			print("|")
			print("|")
			print("|")
			print("|")
			print("|______________|")
			print("|______________|")
		elif self.count == 2:
			print("You have 8 mistakes left to guess the word or you die")
			print("_____________")
			print("|           |")
			print("|           |")
			print("|")
			print("|")
			print("|")
			print("|")
			print("|______________|")
			print("|______________|")
		elif self.count == 3:
			print("You have 7 mistakes left to guess the word or you die")
			print("_____________")
			print("|           |")
			print("|           |")
			print("|           O")
			print("|")
			print("|")
			print("|")
			print("|______________|")
			print("|______________|")
		elif self.count == 4:
			print("You have 6 mistakes left to guess the word or you die")
			print("_____________")
			print("|           |")
			print("|           |")
			print("|           O")
			print("|           |")
			print("|")
			print("|")
			print("|______________|")
			print("|______________|")
		elif self.count == 5:
			print("You have 5 mistakes left to guess the word or you die")
			print("_____________")
			print("|           |")
			print("|           |")
			print("|           O")
			print("|          -|")
			print("|")
			print("|")
			print("|______________|")
			print("|______________|")
		elif self.count == 6:
			print("You have 4 mistakes left to guess the word or you die")
			print("_____________")
			print("|           |")
			print("|           |")
			print("|           O")
			print("|          -|-")
			print("|")
			print("|")
			print("|______________|")
			print("|______________|")
		elif self.count == 7:
			print("You have 3 mistakes left to guess the word or you die")
			print("_____________")
			print("|           |")
			print("|           |")
			print("|           O")
			print("|          -|-")
			print("|          / ")
			print("|")
			print("|______________|")
			print("|______________|")
		elif self.count == 8:
			print("You have 2 mistakes left to guess the word or you die")
			print("_____________")
			print("|           |")
			print("|           |")
			print("|           O")
			print("|          -|-")
			print("|          / \\")
			print("|")
			print("|______________|")
			print("|______________|")
		elif self.count == 9:
			print("You have 1 mistake left to guess the word or you die")
			print("_____________")
			print("|           |")
			print("|           |")
			print("|           O")
			print("|          -|-")
			print("|         _/ \\")
			print("|")
			print("|______________|")
			print("|______________|")
		elif self.count == 10:
			print("You died!")
			print("_____________")
			print("|           |")
			print("|           |")
			print("|           O")
			print("|          -|-")
			print("|         _/ \\_")
			print("|")
			print("|______________|")
			print("|______________|")

	def RandomWord(self):

		with open(self.filename, "r") as f:
			all_opts = f.read().split()
			animal = all_opts[3::3]
			place = all_opts[4::3]
			food = all_opts[5::3]

		opts = {"Animal" : animal, "Place" : place, "Food" : food}
		category = random.choice(["Animal","Place","Food"])
		game_word = random.choice(opts[category])
		print("The category is...")
		print(category)
		return game_word

	def Replay(self):

		resp = str(input("Would you like to play again? Y/N: ")).upper()
		if resp == "N":
			return
		elif resp == "Y":
			self.count = 0
			self.let_used = []
			self.complete = False
			self.Gameplay()

	def Gameplay(self):
		
		word = self.RandomWord().lower()
		disp = list("_"*len(word))
		guess = "".join(list("_ "*len(word)))

		print("Take your first guess...")
		print(guess)
		while guess != word:
			lguess = input("Guess: \n")
			while lguess in self.let_used or len(lguess) != 1 or lguess in ['1','2','3','4','5','6','7','8','9'] or lguess.isalnum() == False:
				lguess = input("Try again: \n")
			self.let_used.append(lguess)
			if (lguess in word) == False:
				self.count += 1
			elif lguess in word:
				temp = 0
				for i in word:
					if lguess != i:
						temp += 1
					elif lguess == i:
						disp[temp] = lguess
						temp += 1
			guess = "".join(disp)
			print(self.let_used)
			print("".join(disp))
			self.PicUpdate()
			if self.count >= 10:
				break

		guess = "".join(disp)
		if guess == word:
			self.complete = True
			print("You Win!")
		self.Replay()

game = Hangman("hm.txt")
game.Gameplay()