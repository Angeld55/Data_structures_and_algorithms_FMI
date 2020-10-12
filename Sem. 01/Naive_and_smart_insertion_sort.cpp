template <class T>
void swap(T* arr,int i ,int j)
{
 T temp = arr[i];
 arr[i]=arr[j];
 arr[j]=temp;
}
template <class T>
void NaiveInsertionSort(T* arr,int len) 
{
    for(int i = 1;i<len;i++)
    {
        T elIndex = i;
        while(elIndex>0&&arr[elIndex]<arr[elIndex-1])
        {
         swap(arr,elIndex,elIndex-1);
         elIndex--;
        }
         
    }
}
template <class T>
void InsertionSort(T* arr,int len)
{
    for(int i =1;i<len;i++)
    {
        T element = arr[i];
        int index = i-1;
        while(index>=0&&arr[index]>element)
        {
            arr[index+1]=arr[index];
            index--;
        }
        arr[index+1]=element;
    }
}
