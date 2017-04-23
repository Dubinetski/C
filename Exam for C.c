/*
Разработать программу хранения рецептов.
При запуске программа показывает меню.
Меню:
1.  Добавление рецепта
2.  Просмотр рецепта
3.  Редактирование рецепта
4.  Удаление рецепта
5.  Выход

Каждый рецепт должен содержать следующую информацию :
1.  Дату создания рецепта
2.  Имя рецепта
3.  Текст рецепта
4.  Рейтинг(от 1 до 10)

Пункт №1 спрашивает имя рецепта на английском языке(или транслите).Это имя в
последствии будет именем файла на файловой системе в котором будет лежать весь тест.
Расширение файла - *.recipe. Далее программа спрашивает текст рецепта и рейтинг.

Пункт №2 выводит список рецептов на файловой системе(файлы с маской *.recipe рядом
с приложением) у которых размер файла больше 0. Далее выводит на экран содержимое
рецепта(дата, имя, текст, рейтинг).

Пункт №3 выводит список рецептов на файловой системе(файлы с маской *.recipe рядом
с приложением) у которых размер файла больше 0. Затем программа спрашивает новый
текст рецепта, который заменит весь текущий текст.

Пункт №4 выводит список рецептов на файловой системе(файлы с маской *.recipe рядом
с приложением), затем спрашивает какой из тестов надо удалить и очищает  файл(размер 0).

Пункт №5 – выход из программы.

Очистка файла : можно открыть файл в режиме "w" и закрыть.
*/


#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>

enum MenuMain
{
	PrintRecipeList = '1',
	AddRecipe = '2',
	ReadRecipe = '3',
	EditRecipe = '4',
	DeleteRecipe = '5',
	Esc = '\x1b',
	Enter = '\r'
};

enum Constants
{
	RecipeFildCount = 4,
	FileNameLength = 50,
	FileExtensionLength = 7,
	RecipeTextBuffer = 256,
};

void findRecipesOnDisk(char* fileMask, char*** recipeNameList, int* recipeCount);
void printRecipeList(char** recipeNameList, int* recipeCount, char* statusString);
void printRecipe(struct Recipe* printingRecipe);
void addNewRecipe(struct Recipe* newRecipe, char*** recipeNameList, int* recipeCount, char* statusString);
void getLocalDateAndTime(char** locatTime);
void readRecipe(struct Recipe* readingRecipe, char*** recipeNameList, int* recipeCount, char* statusString);
void editRecipe(struct Recipe* editRecipe, char** recipeNameList, int* recipeCount, char* statusString);
void deleteRecipe(char*** recipeNameList, int* recipeCount, char* statusString);
void getNewRecipe(struct Recipe* newRecipe, char** recipeNameList, int recipeCount);
void getFildOfRecipe(char* fildName, char** readingString);
void addRecipeOnDisk(struct Recipe* newRecipe);
void addRecipeInList(struct Recipe* newRecipe, char*** recipeNameList, int* recipeCount);
void readRecipeFromFile(char* recipeName, struct Recipe* activeRecipe);
void editContentOfRecipe(char* recipeName, struct Recipe* activeRecipe);
void deleteRecipeFromDisk(char* recipeName);
void deleteRecipeFromList(char*** recipeNameList, int* recipeCount, int delRecipeNumber);
void getRecipeNumber(char* printingString, int* recipeNumber, int recipeCount);
bool isConfirmToDeleteGetted(char* fileName);
void makeString(char** rezultString, int stringsCount, ...);
void closeRecipe(struct Recipe* activeRecipe, char** recipeList, int* recipeCount);
bool isNameIsAbsenceInList(char* nameRecipe, char** recipeNameList, int recipeCount);
void getNumber(char* inviteString, short* returnedNumber, short minValue, short maxValue);
bool isPointerEmpty(char* ptrRecipe);
void showMainMenu(char* statusString);
char menuChoice();
void backToMenu();

/*рецепт*/
struct Recipe
{
	char* name;
	char* date;
	short* reit;
	char* text;
};

int main(int argc, char* argv[])
{
	char* fileName = "*.recipe";					// Маска файла

	int* recipeCount = (int*)malloc(sizeof(int));	// Колличество рецептов на диске
	*recipeCount = 0;

	char** recipeNameList = NULL;

	findRecipesOnDisk(fileName, &recipeNameList, recipeCount);	// Список названий рецептов

	struct Recipe* activeRecipe = (struct Recipe*)malloc(sizeof(struct Recipe));	// Активный рецепт
	activeRecipe->name = activeRecipe->date = activeRecipe->text = NULL;
	activeRecipe->reit = (short*)malloc(sizeof(short));

	char* statusString = (char*)malloc(50);
	strcpy(statusString, "Hello. Program work with collection of recipes.");

	while (true)
	{
		showMainMenu(statusString);

		switch (menuChoice())
		{
		case PrintRecipeList:
			printRecipeList(recipeNameList, recipeCount, statusString);
			if (*recipeCount > 0) backToMenu();
			break;
		case AddRecipe:
			addNewRecipe(activeRecipe, &recipeNameList, recipeCount, statusString);
			break;
		case ReadRecipe:
			readRecipe(activeRecipe, &recipeNameList, recipeCount, statusString);
			break;
		case EditRecipe:
			editRecipe(activeRecipe, recipeNameList, recipeCount, statusString);
			break;
		case DeleteRecipe:
			deleteRecipe(&recipeNameList, recipeCount, statusString);
			break;
		case Esc:
			closeRecipe(activeRecipe, recipeNameList, recipeCount);
			free(statusString);
			return 0;
		default:
			break;
		}
	}
}

/* Поиск рецептов на жестком диске.*/
void findRecipesOnDisk(char* fileMask, char*** recipeNameList, int* recipeCount)
{
	WIN32_FIND_DATAA findData;
	HANDLE searchResult = FindFirstFileA(fileMask, &findData);
	char fileName[FileNameLength] = "";

	if (searchResult != INVALID_HANDLE_VALUE)
	{
		do
		{
			if (findData.nFileSizeLow > 0)
			{
				strcpy(fileName, findData.cFileName);
				fileName[strlen(fileName) - FileExtensionLength] = '\0';		// Удаляем расширение .recipe из имени файла
				*recipeNameList = (char**)realloc(*recipeNameList, sizeof(char*) * ((*recipeCount) + 1));
				(*recipeNameList)[*recipeCount] = (char*)malloc(strlen(fileName) + 1);
				strcpy((*recipeNameList)[(*recipeCount)++], fileName);
			}
		} while (FindNextFileA(searchResult, &findData));
	}
	FindClose(searchResult);
	return recipeNameList;
}

/* Печать списка имеющихся рецептов */
void printRecipeList(char** recipeNameList, int* recipeCount, char* statusString)
{
	if (!isPointerEmpty(recipeNameList) && recipeCount > 0)
	{
		system("cls");
		printf("List of resipe on disk:\n\n");
		printf("%s%7s\n", "#", "Name");
		for (int i = 0; i < *recipeCount; i++)
		{
			printf("%-4i%-10s\n", i + 1, recipeNameList[i]);
		}
		makeString(&statusString, 0);
	}
	else
	{
		makeString(&statusString, 1, "There is no recipe on disk.");
	}
}

/* Вывод содержимого рецепта на консоль */
void printRecipe(struct Recipe* printingRecipe)
{
	system("cls");
	printf("Title: %s\n\n", printingRecipe->name);
	printf("Date: %s\n", printingRecipe->date);
	printf("Reit: %hu\n", *(printingRecipe->reit));
	printf("Text: %s\n", printingRecipe->text);
}

/* Добавление нового рецепта */
void addNewRecipe(struct Recipe* newRecipe, char*** recipeNameList, int* recipeCount, char* statusString)
{
	getNewRecipe(newRecipe, *recipeNameList, *recipeCount);
	addRecipeOnDisk(newRecipe);
	addRecipeInList(newRecipe, recipeNameList, recipeCount);
	makeString(&statusString, 3, "The recipe \"", newRecipe->name, "\" was added.");
}

/* Получить текущую дату и время*/
void getLocalDateAndTime(char** locatTime)
{
	time_t rawtime;
	struct tm* timeinfo;
	time(&rawtime);
	timeinfo = localtime(&rawtime);
	char* strTime = asctime(timeinfo); // Время создания рецепта
	strTime[strlen(strTime) - 1] = 0;
	*locatTime = (char*)realloc(*locatTime, strlen(strTime) + 1);
	strcpy(*locatTime, strTime);
}

/* Чтение рецепта с диска*/
void readRecipe(struct Recipe* readingRecipe, char*** recipeNameList, int* recipeCount, char* statusString)
{
	printRecipeList(*recipeNameList, recipeCount, statusString);
	if (*recipeCount > 0)
	{
		int recipeNumber;	// Номер выбранного рецепта
		getRecipeNumber("read", &recipeNumber, *recipeCount);
		readRecipeFromFile((*recipeNameList)[recipeNumber - 1], readingRecipe);
		printRecipe(readingRecipe);
		makeString(&statusString, 0);
		backToMenu();
	}
}

/* Редактирование рецепта на диске */
void editRecipe(struct Recipe* editRecipe, char** recipeNameList, int* recipeCount, char* statusString)
{
	printRecipeList(recipeNameList, recipeCount, statusString);
	if (*recipeCount > 0)
	{
		int recipeNumber;	// Номер редактируемого рецепта
		getRecipeNumber("edit", &recipeNumber, *recipeCount);
		readRecipeFromFile(recipeNameList[recipeNumber - 1], editRecipe);
		printRecipe(editRecipe);
		editContentOfRecipe(recipeNameList[recipeNumber - 1], editRecipe);
		makeString(&statusString, 3, "The recipe \"", editRecipe->name, "\" was edited.");
		backToMenu();
	}
}

/* Удаление содержимого рецепта на диске */
void deleteRecipe(char*** recipeNameList, int* recipeCount, char* statusString)
{
	printRecipeList(*recipeNameList, recipeCount, statusString);
	if (*recipeCount > 0)
	{
		int recipeNumber;	// Номер удаляемого рецепта
		getRecipeNumber("delete", &recipeNumber, *recipeCount);

		if (isConfirmToDeleteGetted((*recipeNameList)[recipeNumber - 1]) == false)
		{
			makeString(&statusString, 0);
			return;
		}
		makeString(&statusString, 3, "The recipe \"", (*recipeNameList)[recipeNumber - 1], "\" was deleted.");
		deleteRecipeFromDisk((*recipeNameList)[recipeNumber - 1]);
		deleteRecipeFromList(recipeNameList, recipeCount, recipeNumber - 1);
	}
}


/* Получение нового рецепта от пользователя */
void getNewRecipe(struct Recipe* newRecipe, char** recipeNameList, int recipeCount)
{
	system("cls");
	printf("Fill the filds of the new recipe\n\n");
	while (true)
	{
		getFildOfRecipe("Name", &(newRecipe->name));

		if (isNameIsAbsenceInList(newRecipe->name, recipeNameList, recipeCount))
		{
			break;
		}
		printf("This recipe already is present on disk!\nChoise the another name of recipe or delete the existing file.\n\n");
	}
	getFildOfRecipe("Text", &(newRecipe->text));
	getNumber("Rating (1..10): ", newRecipe->reit, 1, 10);
	getLocalDateAndTime(&(newRecipe->date));
}

/*Получение строки от пользователя с сохранением ее в "куче"*/
void getFildOfRecipe(char* fildName, char** readingString)
{
	printf("%s: ", fildName);
	char gotUserString[RecipeTextBuffer];	//полученная от пользователя информация
	gets(gotUserString);
	*readingString = realloc(*readingString, strlen(gotUserString) + 1);
	strcpy(*readingString, gotUserString);
}

/* Добавление нового рецепта на диск */
void addRecipeOnDisk(struct Recipe* newRecipe)
{
	char* fileName = NULL;
	makeString(&fileName, 2, newRecipe->name, ".recipe");
	FILE* fileNewRecipe = fopen(fileName, "w");		// Создать файл с именем как название рецепта
	if (fileNewRecipe == NULL)
	{
		printf("Error created file of new recipe.\n");
		exit(1);
	}
	char reit[3];
	itoa(*newRecipe->reit, reit, 10);
	char* saveString = (char*)malloc(strlen(newRecipe->date) + strlen(newRecipe->text) + strlen(reit) + 4);
	makeString(&saveString, 6, newRecipe->date, ";", reit, ";", newRecipe->text, ";");
	fprintf(fileNewRecipe, "%s", saveString);
	fclose(fileNewRecipe);
	free(fileName);
	free(saveString);
}

/* Добавление рецепта в список рецептов */
void addRecipeInList(struct Recipe* newRecipe, char*** recipeNameList, int* recipeCount)
{
	*recipeNameList = (char**)realloc(*recipeNameList, ((*recipeCount) + 1) * sizeof(char*));
	(*recipeNameList)[*recipeCount] = (char*)malloc(strlen(newRecipe->name) + 1);
	strcpy((*recipeNameList)[(*recipeCount)++], newRecipe->name);
}

/* Считывание рецепта из файла */
void readRecipeFromFile(char* recipeName, struct Recipe* activeRecipe)
{
	char* fileName = (char*)malloc(1);
	makeString(&fileName, 2, recipeName, ".recipe");
	FILE* fileRecipe = fopen(fileName, "r");		// Файл рецепта (чтение)

	if (fileRecipe == NULL)
	{
		printf("Error open file %s", fileName);
		exit(1);
	}

	fseek(fileRecipe, 0, SEEK_END);
	int lenStringInFile = ftell(fileRecipe);	// Длина строки в файле

	char* readString = (char*)malloc(lenStringInFile);	// Считанная из файла строка
	char** recipeFildArray = (char**)malloc(RecipeFildCount * sizeof(char*));	// Массив из полей рецепта

	fseek(fileRecipe, 0, SEEK_SET);

	char* tmpString;
	int i = 0;
	while (!feof(fileRecipe))
	{
		fgets(readString, lenStringInFile, fileRecipe);
		tmpString = strtok(readString, ";");	// Разбиение строки на поля по разделителям
		while (i < RecipeFildCount)
		{
			if (tmpString == NULL)
			{
				break;
			}
			recipeFildArray[i] = malloc(strlen(tmpString) + 1);
			strcpy(recipeFildArray[i++], tmpString);
			tmpString = strtok('\0', ";");
		};
	}
	makeString(&activeRecipe->name, 1, recipeName);
	makeString(&activeRecipe->date, 1, recipeFildArray[0]);
	*activeRecipe->reit = atoi(recipeFildArray[1]);
	makeString(&activeRecipe->text, 1, recipeFildArray[2]);

	fclose(fileRecipe);
	free(readString);
	free(fileName);
	for (int i = 0; i < RecipeFildCount - 1; i++)
	{
		free(recipeFildArray[i]);
	}
	free(recipeFildArray);
}

/* Редактирование текста рецепта */
void editContentOfRecipe(char* recipeName, struct Recipe* activeRecipe)
{
	readRecipeFromFile(recipeName, activeRecipe);

	printf("\n\nNew text of recipe:\n", recipeName);
	char newTextRecipe[256];	// Новый текст рецепта
	gets(newTextRecipe);
	activeRecipe->text = (char*)realloc(activeRecipe->text, strlen(newTextRecipe) + 1);
	strcpy(activeRecipe->text, newTextRecipe);

	addRecipeOnDisk(activeRecipe);
}

/* Удаление рецепта с диска (очистка содержимого) */
void deleteRecipeFromDisk(char* recipeName)
{
	char* fileName = (char*)malloc(1);
	makeString(&fileName, 2, recipeName, ".recipe");
	FILE* fileRecipe = fopen(fileName, "w");		// Открытый для записи файл
	if (fileRecipe == NULL)
	{
		printf("Can't delete file %s", recipeName);
		exit(1);
	}
	fclose(fileRecipe);
	free(fileName);
}

/* Удаление рецепта из списка */
void deleteRecipeFromList(char*** recipeNameList, int* recipeCount, int delRecipeNumber)
{
	free((*recipeNameList)[delRecipeNumber]);
	for (int i = delRecipeNumber; i < (*recipeCount) - 1; i++)
	{
		(*recipeNameList)[i] = (*recipeNameList)[i + 1];
	}
	*recipeNameList = (char**)realloc(*recipeNameList, (--(*recipeCount)) * sizeof(char*));
}

/* Получить номер рецепта */
void getRecipeNumber(char* printingString, int* recipeNumber, int recipeCount)
{
	while (true)
	{
		printf("\nThe number of recipe to %s <1..%i>: ", printingString, recipeCount);
		char countOfReadingValues = scanf("%i", recipeNumber);
		while (getchar() != '\n') {}
		if (countOfReadingValues == 1 && *recipeNumber >= 1 && *recipeNumber <= recipeCount)
		{
			return;
		}
		else
		{
			printf("Incottect number of recipe!\n");
		}
	}
}

/* Подтверждает ли пользователь удаление файла? */
bool isConfirmToDeleteGetted(char* fileName)
{
	printf("\nWARNING!\nAfter deleted restore the recipe to be impossible.\n");
	printf("You realy want to delete the recipe \"%s\"?\n\n", fileName);
	printf("Pres ENTER to confirm, or ESC for cancel.");
	while (true)
	{
		switch (getch())
		{
		case Esc:
			return false;
		case Enter:
			return true;
		default:
			break;
		}
	}
}

/* Склейка строк в одну */
void makeString(char** rezultString, int stringsCount, ...)
{
	va_list args;
	va_start(args, stringsCount);
	*rezultString = (char*)realloc(*rezultString, 2);
	strcpy(*rezultString, "");

	while (stringsCount--)
	{
		char* str = va_arg(args, char*);
		*rezultString = (char*)realloc(*rezultString, strlen(*rezultString) + strlen(str) + 1);
		strcat(*rezultString, str);
	}
	va_end(args);
}

/* Освобождает память в "куче" выделенную для работы программы */
void closeRecipe(struct Recipe* activeRecipe, char** recipeList, int* recipeCount)
{
	free(activeRecipe->name);
	free(activeRecipe->date);
	free(activeRecipe->text);
	free(activeRecipe->reit);
	free(activeRecipe);
	for (int i = 0; i < *recipeCount; i++)
	{
		free(recipeList[i]);
	}
	free(recipeList);
	free(recipeCount);
}

/* Проверка отсутствия файла с заданным именем */
bool isNameIsAbsenceInList(char* nameRecipe, char** recipeNameList, int recipeCount)
{
	for (int i = 0; i < recipeCount; i++)
	{
		if (stricmp(nameRecipe, recipeNameList[i]) == 0)
		{
			return false;
		}
	}
	return true;
}

/* Получение от пользователя одного целого числа в заданном диапазоне */
void getNumber(char* inviteString, short* returnedNumber, short minValue, short maxValue)
{
	char check; 					//колличество успешно считанных значений
	do
	{
		printf("%s", inviteString);
		check = scanf("%hu", returnedNumber);
		while (getchar() != '\n') {}
		if ((check == 1) && (*returnedNumber <= maxValue) && (*returnedNumber >= minValue))
		{
			break;
		}
		printf("Incorrect number. Pleasee try again.\n");
	} while (true);
}

/* Указатель пустой? */
bool isPointerEmpty(char* ptrRecipe)
{
	if (ptrRecipe == NULL)
	{
		return true;
	}
	return false;
}

/*Отобрзить главное меню*/
void showMainMenu(char* statusString)
{
	system("cls");
	printf("%s\n\n", statusString);
	printf("Choise the point of menu...\n");
	printf("1   Print list\n");
	printf("2   Add new\n");
	printf("3   Read\n");
	printf("4   Edit text\n");
	printf("5   Delete\n");
	printf("ESC EXIT.\n\n");
}

/*Выбор пункта главного меню*/
char menuChoice()
{
	while (true)
	{
		char pressKey = getch(); //нажатая клавиша
		switch (pressKey)
		{
		case PrintRecipeList:
		case AddRecipe:
		case ReadRecipe:
		case EditRecipe:
		case DeleteRecipe:
		case Esc:
			return pressKey;
		default:
			break;
		}
	}
}

/* Возврат в меню */
void backToMenu()
{
	printf("\nPress any key to return to menu...");
	getch();
}