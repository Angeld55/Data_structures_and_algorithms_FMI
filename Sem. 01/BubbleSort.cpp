template <class T>
void swap(T* arr,int i ,int j)
{
 T temp = arr[i];
 arr[i]=arr[j];
 arr[j]=temp;
}

template <class T>
void BubbleSort(T* arr,int len)
{
    for(int j = 0;j<len;j++)
    {
        bool isSwapped= false;
        for(int i = 0;i<len-1-j;i++)
        {
            if(arr[i]>arr[i+1])
            {
             swap(arr,i,i+1);
             isSwapped=true;
            }
        }
        if(!isSwapped)//Масив дали вече е сортиран? 
            return;
     }
}
