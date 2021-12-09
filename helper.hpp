/* 
    helper functions
 */


#include <vector>
#include <string>

// print a variable's name
#define GET_VARIABLE_NAME(Variable) (#Variable)

//super simple timer
class ssTimer
{
    // adapteed from:
    // https://stackoverflow.com/questions/22387586/measuring-execution-time-of-a-function-in-c
    std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
    bool started, ended;

    public:      
        ssTimer(){
            started = ended = false;
        }
        void startTimer(){
            start = std::chrono::high_resolution_clock::now();
            started = true;
        }

        void endTimer(){
            end = std::chrono::high_resolution_clock::now();
            ended = true;
        }
        void clearTimer(){
            // start = end = 0;
            started = ended = false;
        }

        void printTimeElapsed(){

            if(!started || !ended){
                std::cout << "Timer error: never started or ended" << std::endl;
            }
            /* Getting number of milliseconds as an integer. */
            // auto ms_int = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

            /* Getting number of milliseconds as a double. */
            std::chrono::duration<double, std::milli> ms_double = end - start;

            // std::cout << ms_int.count() << "ms\n";
            std::cout << ms_double.count() << "ms" << std::endl;
        }

};

int random_in_range(int M = 28, int N = 35)
{
    return (int)((double)rand() / ((double)RAND_MAX + 1) * N);
}

void fill_vector_with_random_values(std::vector<int> &v, size_t count, int M, int N)
{
    v.reserve(count);
    for (size_t i = 0; i < count; ++i)
    {
        v.push_back(random_in_range(M, N));
    }
}

void fill_vector_with_unique_increasing_values(std::vector<int> &v, size_t count, int start=0)
{
    v.reserve(count);
    for (size_t i = start; i < count; ++i)
    {
        v.push_back( i );
    }
}

void test(std::string x)
{
    std::cout << x;
}

/* 
    returns an index where the match is found
    or -1 for no match
 */
template<class T>
int find_in_vec(std::vector<T> vec, T element)
{
    for (int i = 0; i < vec.size(); ++i)
    {
        if (vec[i] == element)
            return i;
    }

    // not found
    return -1;
}

template <class T>
void print_vector(std::vector<T> vec, std::string name, size_t printLimit = -1)
{
    size_t count = 0;
    std::cout << "printing vector: " << name << "\n";
    for (auto x : vec)
    {
        if (printLimit != -1){
            count++;
            if (count > printLimit) break;
        }
        std::cout << x << std::endl;
    }
}

/* 
    matching elements in vec_a to keys in vec_b
    storing matching pairs in joinedVector
 */
template <class T>
void join_vectors(const std::vector<T> vec_a, const std::vector<T> vec_b, std::vector<T> &joinedVector)
{
    for (auto elem : vec_a)
    {
        T temp = find_in_vec(vec_b, elem);
        joinedVector.emplace_back(temp);
    }
}
/* 
    split a vector into partial pieces
 */
template <class T>
void split_vector(std::vector<T> inputVector, std::vector<std::vector<T>> &partialVectors, size_t pieceCount)
{
    // max number of partial vectors = partialvector.size() = 1
    size_t pieceSize = inputVector.size() / pieceCount;

    if (inputVector.size() % pieceCount != 0)
        pieceSize += 1;

    pieceSize = std::min(pieceSize, inputVector.size());
    for(size_t i = 0; i < inputVector.size(); i += pieceSize) 
    {
        //get last element of partial vector
        auto last = std::min(inputVector.size(), i + pieceSize);
        //place partial vector into vector of partial vectors
        partialVectors.emplace_back(inputVector.begin() + i, inputVector.begin() + last);
    }
}
/* 
    recombine partial vectors
 */
template <class T>
void combine_vectors(std::vector<std::vector<T>> inputVectors, std::vector<T> &fullVector)
{
    for(auto &vec : inputVectors) 
    {
        fullVector.insert(fullVector.end(), vec.begin(), vec.end());
    }
}

template <class T>
void join_vectors_multithreaded(const std::vector<T> vec_a, const std::vector<T> vec_b, std::vector<T> &joinedVector, const size_t threadCount=1)
{
    using namespace std;

    // vector of threads
	vector<thread> threads;

    vector<vector<T>> partialVectors;
    split_vector(vec_a, partialVectors, threadCount);
    vector<vector<T>> partialJoinedVectors(threadCount);

    cout << "number of partial vectors: " <<partialVectors.size() << endl;

    // init all threads
	for (size_t i = 0; i < threadCount; ++i)
	{
        /* 
            split vectors to be evenly worked on by threads
            split vec_a 
            pass whole vec_b to all threads
         */
        cout << "calling thread: " << i << "\n";

		threads.push_back(thread(join_vectors<T>, partialVectors[i], vec_b, ref(partialJoinedVectors[i])) );
	}

    // wait for all threads to end
	for (auto &th : threads)
	{
		th.join();
	}

    // combine results
    combine_vectors(partialJoinedVectors, joinedVector);

}

// class ssTable
// {
//     //private
//     // std::map<std:string, int> mapNames
//     // std::vector<std::map> maps;
//     std::vector<std::vector<int>> tables;

//     public:
//         ssTable();
//         void add_table(std::string name, )

// };