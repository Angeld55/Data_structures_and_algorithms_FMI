
# Недетерминиран стеков автомат

  - Реализирайте недетерминистичен стеков авомат.
  - Всяко правило е от вида:
<Текущо състояние, прочетена буква от лентата, връх на стека, състояние в което отиваме, с какво заместваме върха на стека>

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

##### Пример за езика L = {ww^rev | n \in {a,b}* }

```c++
int main()
{
    NondeterministicPushdownAutomaton automation2(3); //3 initial states
    
    automation2.makeStateFinal(2);    
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

