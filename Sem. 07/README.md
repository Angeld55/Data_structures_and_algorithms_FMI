
# Задача 1: Недетерминиран стеков автомат

  - Реализирайте недетерминистичен стеков авомат.
  - Всяко правило е от вида: 
 

####(Текущо състояние, прочетена буква от лентата, връх на стека, състояние в което отиваме, с какво заместваме върха на стека)

##### Пример за езика L = {a^n b^n | n \in N}


```c++
int main()
{
    NondeterministicPushdownAutomaton automation(3); //3 initial states
    
    automation.makeStateFinal(2);    
    automation.addTransition(0,'a','#', 0, "A#");
    automation.addTransition(0,'a','A', 0, "AA");
    automation.addTransition(0,'$','#', 2, "$");
    automation.addTransition(0,'b','A', 1, "$");
    automation.addTransition(1,'b','A', 1, "$");
    automation.addTransition(1,'$', '#', 2, "$");'  
    
    automation.accepts("aaabbb"); //true
    automation.accepts("abb"); //false
    }
```

##### Пример за езика L = {ww^rev | n \in N}

```c++
int main()
{
    NondeterministicPushdownAutomaton automation2(3); //3 initial states
    
    automation2.makeStateFinal(3);    
    automation2.addTransition(0,'a','#', 0, "A#");
    automation2.addTransition(0,'b','#', 0, "B#");
    automation2.addTransition(0,'$','#', 2, "$");
    
    automation2.addTransition(0,'a','A',0,"AA");
    automation2.addTransition(0,'a','A',1,"$");
    
    automation2.addTransition(0,'b','B',0,"BB");
    automation2.addTransition(0,'b','B',1,"$");
    
    automation2.addTransition(0,'b','A',0,"BA");
    automation2.addTransition(0,'a','B',0,"AB");
    
    automation2.addTransition(1,'a', 'A', 1, "$");
    automation2.addTransition(1,'b', 'B', 1, "$");
    
    automation2.addTransition(1,'$','#', 2, "$");
    
    automation2.accepts("abbba"); //true
    automation2.accepts("abab"); //false
    
    
}
```

# Задача 2:

## Реализирайте функция, която приема свързан списък и премахва всяка последователност от поредни върхове, чиято сума на елементите е 0.


Пример: 

**Вход: 99 3 -3  6 -10 4 8 6 2 -8**

**Изход: 99 8**

# Задача 3: Реализирайте функцията *map* за едносвързани списъци.
# Задача 4: Реализирайте функцията *filter* за едносвързани списъци.

