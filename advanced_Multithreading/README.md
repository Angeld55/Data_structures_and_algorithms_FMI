

# Многонишково програмиране 
Има машини с различен брой ядра - 4,8 и тн. Има повече работници.
Искаме да се възползваме от тези ядра и да вършим повече работа за единица време.
Защо да използваме много нишки?

 - бързодействие
 - скалируемост 
 - разделяне на задачите
 
Скалируемост - да напишем програмата днес, но да работи по-бързо след време.
Процесорите до към 2005/2006 тяхната честота (или MHz/GHz) стават все повече и кодът, който изпълняват се изпълнява по-бързо и по-бързо.
По някое време това става непрактично (че даже и невъзможно), защото когато се увеличава честотата на процесора трябва да направим компонентите по-малки (за да не променяме големината на процесора) е на процесорът му трябва все повече ток (което означава, че се генерира все повече топлина и трябва някой да го охлажда).
За това слагат повече процесори на едно място - или в един чип се слагат повече ядра.

Ако преди сме писали програмата и тя става по-бърза на нов хардуер, вече не става по-бърза, но се появяват повече ядра.

В обобщение: Трябва да пишем многонишкови програми и трябва да се интересуваме от хардуерът, който ги изпълнява.

### Трансформиране на алгоритъм, който работи на една нишка

- разделяме на зависима и независима част
- независимата част се разделя на подазадачи
- подзадачите се изчисляват паралелно
- резултатите се акумулират.


### В STL

 - thread(F) { startNewThread(F); } - започва F на нова нишка. [F е указател към функция или обект, който има оператор ()]. F се изпълнява на РАЗЛИЧНА нишка от тази, от която сме го стартирали.
 - join() {waitForThread(F)); } - изчакваме F да приключи. Трябва да внимаваме, да не се хвърли изключение в нишката (не трябва да излиза извън нея).
 - detach() - вече не ни интересува тази нишка. Нашият std::thread обект не се свързва с тази нишка.
 - joinable() - проверява дали по-рано не сме казали detach(). Проверява дали обект се следи от нишката.

### Пример
```c++
struct Task
{
 //entry point for thread (executing this task)
	virtual void run(size_t threadIndex, size_t threadCount) = 0;
	virtual ~Task() = default;
};
```
Сумиране на елементи в масив.
```c++
struct ParallelSum : Task
{
	const std::vector<int>& arr;	
	int sum = 0;

	ParallelSum(const std::vector<int>& arr) : arr(arr){}

	void run(size_t threadIndex, size_t threadCount) override
	{
		for (size_t i = threadIndex; i < arr.size(); i += threadCount)
			sum += arr[i];
	}
};
```
**Проблем - споделена памет**
При четенето на стойността на sum и запазването в регистъра, може да има стара стойност (непосредствено преди някое инкрементиране).

```c++
struct ParallelSum : Task
{
	const std::vector<int>& arr;	
	std::vector<int> tempSum;

	ParallelSum(const std::vector<int>& arr) : arr(arr), tempSum(threadCount){}

	void run(size_t threadIndex, size_t threadCount) override
	{
		for (size_t i = threadIndex; i < arr.size(); i += threadCount)
			tempSum[i] += arr[i];
	}
	void afterThreads()
	{
		for(size_t i = 0; i < threadCount; i++)
			sum += tempSum[i];
	}
};
```
**Проблем - false sharing**
.	.

```c++
struct ParallelSum : Task
{
	const std::vector<int>& arr;	
	std::vector<int> tempSum;

	ParallelSum(const std::vector<int>& arr) : arr(arr), tempSum(threadCount){}

	void run(size_t threadIndex, size_t threadCount) override
	{
		int currentSum = 0;
		for (size_t i = threadIndex; i < arr.size(); i += threadCount)
			currentSum += arr[i];
		tempSum[i] = currentSum;
	}
	void afterThreads()
	{
		for(size_t i = 0; i < threadCount; i++)
			sum += tempSum[i];
	}
};
```
Ядрата не записват стойности в една и съща променлива, но тези три променливи са една до друга.

Всяко ядро има собствена кеш линия. Но кешовете си комуникират един с друг и си гарантира, че всички записи ще се изпълнят в някакъв ред.

Когато ядрото промени по кеш, кеш линията е маркирана като променена "dirty". Тогава другите ядра трябва да изчака и да види какво е направено и когато се актуализира, тогава мога да се правят промени.

Нишките не пишат по едно и също място в паметта, но пишат до достатъчно близки места в паметта, така че имплементацията споделя тази памети и се налага да се правят допълнителни действия от процесора.

### Синхронизация
Екслузивен достъп до част от кода (регион, до който може да стигне само 1 нишка). 
 1. std::mutex / std::timed_mutex
 
 Категоризираме **mutex**: 
 - Рекурсивни (в някоя структура от данни, която метод вика друг метод)/ Нерекурсивни
 - За четете и писане и различни нива на достъп
 
 **std::mutex**
 - lock(); 
 - unlock();
 - try_lock();
 
 Разлика между lock() и try_lock(), е че ако mutex-ът е заключен при lock() ще изчака, докато се отключи, а try_lock() направо ще върне false.
 Всяка от тези функции се изпълняват от операционната система, а не се изпълняват от кода. Всяка от тези функции е имплементирана като някаква част от API-то на нашата операционна система.
Как използваме mutex ?

```c++
myMutex.lock();
f(); //shared memory
myMytex.unlock();
```
Ако някой не отключи mutex-а се получава deadlock.
Ако f() хвъли изключение? Изключението търси първия catch по пътя и изпълнява деструктори. В тази ситуация не се отключва mutex-а.
```c++
std::lock_guard<T>
lock_guard(T& currentMutex) {currentMutex.lock();}
~lock_guard() {currentMutex.unlock();},
```
или

```c++
std::unique_lock<T>
unique_lock(T& currentMutex) {currentMutex.lock();}
~unique_lock() { if(locked) currentMutex.unlock();}
lock() { currentMutex.lock(); locked = true; }
unlock() {currentMutex.unlock(); locked = false;}
```
Примери и проблеми:
```c++
	void run(size_t threadIndex, size_t threadCount) override
	{
		m.lock();
		for (size_t i = threadIndex; i < arr.size(); i += threadCount)
			sum += arr[i];
		m.unlock();
	}
```
Това е все едно да изпълняваме на точно една нишка.!

```c++
	void run(size_t threadIndex, size_t threadCount) override
	{
		for (size_t i = threadIndex; i < arr.size(); i += threadCount)
		{
			m.lock();
			sum += arr[i];
			m.unlock();
		}
	}
```
Бявно, защото на всеки елемент заключваме и отключваме, а това са бавни операции.

```c++
	void run(size_t threadIndex, size_t threadCount) override
	{
		int currentSum = 0;
		for (size_t i = threadIndex; i < arr.size(); i += threadCount)
			currentSum += arr[i];
		m.lock();
		sum += currentSum;
		m.unlock();
	}
```
Тук нямаме нужда от допълнителни данни (колкото са броя нишките) и тн.
Не е добра идея, ако имаме много нишки.


```c++
	void run(size_t threadIndex, size_t threadCount) override
	{
		int currentSum = 0;
		for (size_t i = threadIndex; i < arr.size(); i += threadCount)
			currentSum += arr[i];
		std::lock_guard<std::mutex> obj(m); //а не std::lock_guard<std::mutex>(m), защото създава временна променлива, която се изтрива веднага.
		sum += currentSum;
	}
```

 ### Комуникация
 std::condition_variable  -  пращаме съобщение на нишки и ги караме да изчакат нещо да се случи.
 

 - **wait**(std::unique_lock<T>& lck, Predicate p) - {while(!p) wait(lck)} - **отключва** mutex-а,  чакаме да се случи нещо, за да заработи нишката. Предикатът отговаря на въпрса - "тази нишка има ли какво да прави?" Mutex-ът е обвит в std::unique_lock обект, който е заключен предварително.
wait() - mutex-ът се отключва и нишката заспива. Важно: Двете се случват като една операция, за да няма интервал от време между отключването и заспиването. За това се изпълнява с примитив (в windows е event)	
wait() приключва когато някой отвънка извика **notify**.
 - **notify_all()** - събужда всички чакащи.
 - **notify_one()** - събужда една(някоя (операционната система избира една)) чакаща нишка на този std::condition_variable 

notify се прави при отключен mutex!
```c++
	std::condition_variable cv;
	std::mutex m;
	f()
	{
		std::unique_lock<std::mutex> currentLock(m);
		cv.wait(currentLock, pred);
	}
	g()
	{
		if()
		{
			std::lock_guard<std::mutex> guard(m);
			//do stuff
		}
		cv.notify_one();
	}
```
notify_one() се опитва да събуди condition_variable-a. Той събужда нишката заспива на mutex-a. След това продължава, като mutex-а се отключи. За това в STL notify се извиква при отключен mutex.

 ### Проблеми при синхронизация 
 
 - Deadlock
 - livelock
 - Лоша производителност

### Атомарни операции:
Атомарни променливи, които правят атомарни опрации. 
Атомарна операция - неделима. Всякаш ние сме заключили мютекс (процесорът гарантира, че операцията ще се изпълни по атомарен начин и няма да бъде прекъсната от други нишки). Те не могат да се произволно сложни:

 - четене
 - писане
- RMW (read-modify-write)
- CAS (compare-exchange) (прочита от паметта и ако е очакваната стойност, записва новата)

Четенето и писането НЕ са атомарна операции по дефиниция. Ако запазваме Int, който е 4 байта, може да стане на 2 части (от по 2 байта). На модерните процесори нямаме такъв проблем (поне за всички неща, които са до 8 байта).

```c++
std::atomic<T> at;
```

 - store(T newValue); // at = newValue
 - load(); // T x = at;
 - exchange(T newValue); //swap
 - compare_exchange(T& excpected, T newValue); //ако стойнстта на at е expected, заспива newValue, ако не е - записва в excpected стойността на at
 - fetch[add,sub,or,xor,nad] (T argument) //прилага операцията над at и argument.
 - bool isLockFree(); // проверяваме дали има mutex или се поддържа от процесора.
