template <typename T, typename U,typename V>
Triple<T, U, V>::Triple()
{

}

template <typename T, typename U,typename V>
Triple<T, U, V>::Triple(T one, U two, V three) : first{one}, second{two}, third{three}
{

}

template <typename T, typename U,typename V>
Triple<T, U, V>::Triple(Triple<T, U, V>& triple) : first{triple.first}, second{triple.second}, third{triple.third}
{

}

template <typename T, typename U,typename V>
void Triple<T, U, V>::swap(Triple<T, U, V>& triple1, Triple<T, U, V>& triple2)
{
    Triple<T, U, V>& temp{triple1};
    triple1 = triple2;
    triple2 = temp;
}
