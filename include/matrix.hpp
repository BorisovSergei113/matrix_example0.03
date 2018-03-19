#include <iostream>

using namespace std;


template <class Type>
class matrix_t {
    
    static Type ** Create_Matrix(int stroki,int stolbi){  //Либо можно ставить <Type> аезде где вызвается ф-ция и сама вызываемая ф-ция вне класса
        Type **New_Matrix = new Type *[stroki];
        for (int i=0;i<stroki;i++){
            New_Matrix[i]= new Type [stolbi];
        }
        return New_Matrix;
    }
    
private:
    Type ** data;
    unsigned int stroki;
    unsigned int stolbi;
public:
    matrix_t();
    matrix_t(int in_stroki,int in_stolbi);
    matrix_t( matrix_t const & object );
    matrix_t & operator =( matrix_t const & other );
    ~matrix_t();
    
    unsigned int Get_Stroki() const;
    unsigned int Get_Stolbi() const;
    
    matrix_t operator +( matrix_t const & other ) const;
    matrix_t operator -( matrix_t const & other ) const;
    matrix_t operator *( matrix_t const & other ) const;
    
    matrix_t & operator -=( matrix_t const & other );
    matrix_t & operator +=( matrix_t const & other );
    matrix_t & operator *=( matrix_t const & other );
    
    std::istream & read( std::istream & stream );
    std::ostream & write( std::ostream  & stream ) const;
};



template <typename Type>
matrix_t<Type>::matrix_t()
{
    stroki=0;
    stolbi=0;
    data = Create_Matrix(stroki, stolbi);
}

template <typename Type>
matrix_t<Type>::matrix_t(int in_stroki,int in_stolbi){
    stroki=in_stroki;
    stolbi=in_stolbi;
    data = Create_Matrix(stroki, stolbi);
}

template <typename Type>
matrix_t<Type>::matrix_t( matrix_t <Type> const & object )
{
    stroki=object.stroki;
    stolbi=object.stolbi;
    data=Create_Matrix(stroki, stolbi);
    for ( int i = 0; i < stroki; ++i){
        for ( int j = 0; j < stolbi; ++j){
            data[i][j] = object.data[i][j];
        }
    }
}

template <typename Type>

matrix_t<Type> & matrix_t<Type>::operator =( matrix_t<Type> const & other )
{
    if (&other == this) return *this;
    for (int i=0; i<stroki; i++){ //Сначала освобождаем память ,потом узнаем размер ,потом выделяем память.
        delete[] data[i];
    }
    delete[] data;
    stroki=other.stroki;
    stolbi=other.stolbi;
    this->data = Create_Matrix(stroki, stolbi);
    for ( int i = 0; i < stroki; ++i){
        for ( int j = 0; j < stolbi; ++j){
            data [i][j] = other.data[i][j];
        }
    }
    //        cout<<"operator ="<<'\n';
    return *this;
}

template <typename Type>
matrix_t<Type>::~matrix_t()
{
    for (int i=0; i<stroki; i++){
        delete[] data[i];
    }
    delete[] data;
    cout<<'\n';
    
}

template <typename Type>
unsigned int matrix_t<Type>::Get_Stroki() const
{
    return stroki;
}

template <typename Type>
unsigned int matrix_t<Type>::Get_Stolbi() const
{
    return stolbi;
}

template <typename Type>
matrix_t<Type> matrix_t<Type>::operator +( matrix_t<Type> const & other ) const
{
    matrix_t <Type> result(stroki,stolbi);
    for (int i = 0; i< stroki; i++) {
        for (int j = 0 ; j< stolbi; j++) {
            result.data[i][j]=data[i][j]+other.data [i][j];
        }
    }
    return result;
}

template <typename Type>
matrix_t<Type> matrix_t<Type>::operator -( matrix_t<Type> const & other ) const
{
    matrix_t<Type> result(stroki,stolbi);
    for (int i = 0; i< stroki; i++) {
        for (int j = 0 ; j< stolbi; j++) {
            result.data[i][j]=data[i][j]-other.data [i][j];
        }
    }
    return result;
}

template <typename Type>
matrix_t<Type> matrix_t<Type>::operator *( matrix_t <Type> const & other ) const
{
    matrix_t <Type> result(stroki,other.stolbi);
    for (int i = 0; i<stroki; i++) {
        for (int j = 0; j<other.stolbi; j++) {
            result.data[i][j] = 0;
            for (int h = 0; h<stolbi; h++) {
                result.data[i][j] += data[i][h]*other.data[h][j];
            }
        }
    }
    return result;
}

template <typename Type>
matrix_t<Type> & matrix_t<Type>::operator -=( matrix_t <Type> const & other )
{
    stroki=other.stroki;
    stolbi=other.stolbi;
    for (int i = 0; i< stroki; i++) {
        for (int j = 0 ; j< stolbi; j++) {
            data[i][j]=data[i][j]-other.data [i][j];
        }
    }
    return *this;
}

template <typename Type>
matrix_t<Type> & matrix_t<Type>::operator +=( matrix_t <Type> const & other )
{
    stroki=other.stroki;
    stolbi=other.stolbi;
    for (int i = 0; i< stroki; i++) {
        for (int j = 0 ; j< stolbi; j++) {
            data[i][j]=data[i][j]+other.data [i][j];
        }
    }
    return *this;
}

template <typename Type>
matrix_t<Type> & matrix_t<Type>::operator *=( matrix_t<Type> const & other )
{
    matrix_t<Type> copy(*this);
    matrix_t<Type> copy2(other);
    for (int i = 0; i<stroki; i++) {
        for (int j = 0; j<other.stolbi; j++) {
            data[i][j] = 0;
            for (int h = 0; h<stolbi; h++) {
                data[i][j] += copy.data[i][h]*copy2.data[h][j];
            }
        }
    }
    this->stolbi = other.stolbi;
    return *this;
}
template <typename Type>
istream & matrix_t<Type>::read( istream & stream )
{
    unsigned int stroki2 ;
    unsigned int stolbi2 ;
    char symbol ;
    
    bool success = true;
    if( stream >> stroki2 && stream >> symbol && symbol == ',' && stream >> stolbi2 ) {
        Type ** elements = new Type *[ stroki2 ];
        for( unsigned int i = 0; success && i < stroki2; ++i ) {
            elements[ i ] = new Type [ stolbi2 ];
            for( unsigned int j = 0; j < stolbi2; ++j ) {
                if( !( stream >> elements[ i ][ j ] ) ) {
                    success = false;
                    break;
                }
            }
        }
        
        if( success ) {
            for( unsigned int i = 0; i < stroki; ++i ) {
                delete [] data[ i ];
            }
            delete [] data;
            
            stroki = stroki2;
            stolbi = stolbi2;
            data = elements;
        }
        else {
            for( unsigned int i = 0; i < stroki2 ; ++i ) {
                delete [] elements[ i ];
            }
            delete [] elements;
        }
    }
    else {
        success = false;
    }
    
    if( !success ) {
        stream.setstate( ios_base::failbit );
        //            cout<<"ERROR"<<'\n';
    }
    return stream;
}
template <typename Type>
ostream & matrix_t<Type>::write( ostream & stream ) const
{
    
    stream << stroki << "," << stolbi;
    for( unsigned int i = 0; i < stroki; ++i ) {
        stream <<'\n';
        for( unsigned int j = 0; j < stolbi; ++j ) {
            stream << data[ i ][ j ];
            if( j != stroki - 1 ) {
                stream <<' ';
            }
        }
    }
    
    return stream;
}

