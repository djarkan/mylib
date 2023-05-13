namespace mylib
{
template <typename T, typename U,typename V>
class Triple
{
   public:
        Triple();
        Triple(T first, U second, V third);

        T first;
        U second;
        V third;
};
template <typename T, typename U,typename V>
Triple<T, U, V>::Triple()
{

}

template <typename T, typename U,typename V>
Triple<T, U, V>::Triple(T first, U second, V third) : first{first}, second{second}, third{third}
{

}

}
