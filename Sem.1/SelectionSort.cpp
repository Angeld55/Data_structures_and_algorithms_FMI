template <class T>
void swap(T* arr,int i ,int j)
{
 T temp = arr[i];
 arr[i]=arr[j];
 arr[j]=temp;
}
template <class T>
void SelectionSort(T* arr,int size)
{
    for(int i = 0;i<size-1;i++)
    {
        int minIndex=i;
        for(int j=i+1; j<size;j++)
        {
            if(arr[j]<arr[minIndex])
                minIndex=j;
        }
        if(i != minIndex)
          swap(arr,i,minIndex);
    }
}
