


# Комбинаторно генериране (основни комбинаторни обекти)  
  ## Въведение

  

 - **Прости комбинаторни обекти** - броят се с прости рекурентни уравнения.
  
 - **Прости рекурентни уравнения**  - съдържат само събиране и умножение

Рекурсивните генератори са ефикасни, ако имаме само събираме и умножаваме (но не изваждаме)

Съществуват 2 начина за генерирането на комбинаторни обекти:

 - рекурсивно - обикновено следва рекурентното уравнение, което ги брои
 - итеративно - итеративните алгоритми за комбинаторно генериране имат следния вид:
```c++  
combObj = Init
do
{
	print(combObj )
}   while(Next(combObj))
``` 
Тук функцията Next връща лъжа, когато няма следващ обект в избраната наредба.

 - **Ранжиране (ranking)** - ако за обектите има дефиниран порядък, то rank(X) е броят обекти преди X в избраната наредба. Ранжирането задава перфектна хеш функция (няма колизии).
 - **Деранжиране (unranking)** - по дадено число кой обект съотвества. Начин за компресия.
Примерна подредба: **lex**
 (a<sub>1</sub> ...  a<sub>n</sub>) <  (b<sub>1</sub> ...  b<sub>n</sub>), ако за някое k:   a<sub>k</sub> = b<sub>k</sub>  и   a<sub>i</sub> <  b<sub>i</sub> (i = {1 ... k-1})
 - **Сложност** - N (броя на обектите, които искаме да генерираме). Константно време за всеки обект на практика е невъзможно, но ние търсим алгоритъм със сложност O(N). Тогава:
  O(N) /N = О(1) константно време на обект в амортизирания смисъл
Такива алгоритми ще наричаме **CAT**  (**C**onstant **A**mortized **T**ime).

! НЕ броим времето за принтене/друго действие с тези обекти!

## Подмножества  
Репрезентираме като битстринг.  
b_1 b_2 ··· b_n където bi е единица, само ако i-я елемент е включен в множеството.  

### Рекурсивно
За всеки елемент имаме 2 варианта - да го включим в множеството или да не го включим. Тази идея дава директен рекурсивен алгоритъм:

```c++  
void generateAllSubsets(const int* arr, int len, int* bitString, int pos)
{
	if (pos == len)
		print(arr, len, bitString);
	else
	{
		bitString[pos] = 0;
		generateAllSubsets(arr, len, bitString, pos + 1);
		bitString[pos] = 1;
		generateAllSubsets(arr, len, bitString, pos + 1);
	}

}
``` 
Сложността на този алгоритъм се описва със следното рекурентно уравнение:
 
  ![enter image description here](https://i.ibb.co/TgCq5VG/ASDASD.png)
  
което се решава лесно с метода с харектеристичното уравнение - O(2^n).

Следователно алгоритъмът е **CAT**.

 ### Итеративно
 
Т.е лесно може да състави алгоритъм, който по един битстринг дава слеващия - инкрементация с 1 на двоичното число, записано в битстринга - от дясно наляво всички 1-ци правим на 0-ли и първата 0 я правим на 1-ца.

![enter image description here](https://i.ibb.co/SPp1Rp8/Untitled-Diagram-drawio-2.png)
```c++  
bool nextObj(std::vector<int>& bitString)
{
	int i = bitString.size() - 1;

	while (i >= 0 && bitString[i] == 1)
		bitString[i--] = 0;

	if (i < 0)
		return false;

	bitString[i] = 1;

	return true;
}
```  

Давайки директен итеративен алгоритъм за генерирането им:  
```c++  
void generateAllSubsetsIter(const std::vector<int>& v)
{
	std::vector<int> bitString(v.size()); // 0 0 0 0 0 ... 0

	do
	{
		printSubset(bitString, v);
	} while (nextObj(bitString));
}
```  
За да определим сложността преброяваме всички пъти, които сме на ред (*) в алгоритъма. 

 - 2^n - проверката дава лъжа (обектът е готов) и
 - Проверката дава истина за всички стрингове, които след i-тия индекс имат само 1-ци. Пресмятайки броят им получваме:

![enter image description here](https://i.ibb.co/HPsJkrg/2nn.png)

От което следва, че алгоритъмът е **CAT**

 ### Ранжиране
 
За произволно множество лесно може да определим позицията му в подредбата - битстрингът му е това число (записан в двоична бройна система)

![enter image description here](https://i.ibb.co/D1WGk9y/FSDD.png)
  
##  Пермутации

### Рекурсивно
Този алгоритъм е доста прост - предполага, че масивът е инициализиран с някоя пермутация. 
```c++  
void generatePermutations(int* arr, int len, int index)

{

	if (index >= len)
		print(arr, len);
	else
	{
		for (int i = index; i < len; i++)
		{
			std::swap(arr[index], arr[i]);
			generatePermutations(arr, len, index + 1);
			std::swap(arr[index], arr[i]); //back to the original place;
		}

	}

}
```  

 - Алгоритъмът прави размени (повече размени от итеративния), но все пак е **CAT** (t_n = n * t_n-1).
 -   НЕ генерира пермутациите лексикографски подредени.

### Итеративно
Искаме алгоритъм, който ги принтира в лексикографска подредба.

```c++  
bool next(std::vector<int>& arr)

{

	if(arr.size() <= 1)
		return false;

	int k = arr.size() - 2;

	while(k >= 0 && arr[k] > arr[k+1])
		k--;

	if(k < 0)
		return false;

	size_t j = arr.size() - 1;

	while(j>=0 && arr[k] > arr[j])
		j--;

	std::swap(arr[k], arr[j]);

	size_t r = arr.size() - 1;

	size_t s = k + 1;

	while(r > s)
		std::swap(arr[r--],arr[s++]);

	return true;

}
```  
Алгоритъмът търси първият елемент (от дясно наляво),  който е по-малък от предишния. Той се увеличава минимално и останалата част се запълва по възможно най-малкият лексикографски начин.

![enter image description here](https://i.ibb.co/Wy0qMtJ/perms.png)

Алгоритъмът работи чрез размени (swap-ове) на елементите.
Нека с t_n бележим броя размени за да получим всичките n! пермутации.

![enter image description here](https://i.ibb.co/1dfkfw1/fr1.png)

Имаме n групи пермутации с фиксиран първи елемент. При генерирането на всяка група размените, които се извършват са t_n-1.  На n-1 преминавания от една група в друга група имаме (n + 1)/2 размени.
**Полагаме** и:
![enter image description here](https://i.ibb.co/28HYj0F/fr3.png)

Знаем за хиперболичен косинус, че :

![enter image description here](https://i.ibb.co/YytpKvb/fr4.png)

Откъдето следва, че:

![enter image description here](https://i.ibb.co/zFgq44B/fr5.png)

Тогава алгоритъмът е **CAT**.


###  Ранжиране
Rank(31245) ? . Всички пермутации, които започват с 1 и 2 са преди текущата.
Те са 2 * 4 !.  Т.е Rank(31245)  = 2 * 4! + Rank(1245) (в множеството {1,2,4,5}.
adsa
![enter image description here](https://i.ibb.co/F54Kg6j/rank.png)
където π' <sub>i - 1</sub> =πi<sub>i</sub> , ако π<sub>1</sub> > π<sub>i</sub>  и    π'<sub>i-1</sub> =  π<sub>i-1</sub> ако π<sub>1</sub> < π<sub>i</sub>
##  Комбинации

####  Представяния на комбинации
Като битстринг:

![enter image description here](https://i.ibb.co/tHgMqkj/fs-comb-1.png)

Чрез изреждане в нарастващ ред всички k елемента на комбинацията.

![enter image description here](https://i.ibb.co/cbpMYnX/ds-comb-2.png)

За пример:

 A(5,3) =  123, 124, 125, 134, 135, 145, 234, 235, 245, 345

### Итеративно 
#### Процедура next за A(n,k)

Като при всички лексикографски алгортими, може да скарнираме за най-десния елемент, който може да се увеличи. Т.е търсим най-голямата позиция j, такава че a_j < n - k + j

```c++  
bool nextObj(std::vector<size_t>& v, size_t n) //k is v.size()
{
	int j = v.size() - 1;

	while (j >= 0 && v[j] == n - v.size() + j + 1) //(*)
		j--;

	if (j < 0)
		return false;

	v[j]++;

	for (size_t i = j + 1; i < v.size(); i++) //(**)
		v[i] = v[i - 1] + 1;

	return true;
}

```  
Сложността на алгоритъма се определя от това колко пъти е направено сравнението на ред (*) - на ред (**) се правят същия брой сравнения.

 - false: За всеки генериран обект - binom(n,k)
 - true:  binom(n-p, k-p)  всеки път когато a_k−p+1 = n − p + 1 (за 1 ≤ p ≤ k);

Следователно броят сравнения е:

![enter image description here](https://i.ibb.co/6r4LDzg/image.png)

Да разгледаме средно на обект:
![enter image description here](https://i.ibb.co/YPhRShj/sadas.png)
Тогава алгоритъмът е **CAT** за k <= n/2. Ако k >= n/2, то е по-добре да генерираме обратните/комплементарните комбинации.
