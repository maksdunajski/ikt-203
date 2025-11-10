#include <iostream>

enum EGenreFlags {
    Action =        0x0001,
    Comedy =        0x0002,
    Drama =         0x0004,
    Horror =        0x0008,
    SciFi =         0x0010,
    Romance =       0x0020,
    Documentary =   0x0040,
    Thriller =      0x0080,
    Crime =         0x0100,
    Fantasy =       0x0200,
    Animation =     0x0400,
    Adventure =     0x0800
};


// Time: O(1) (fixed number of flags) | Space: O(1)
static std::string GenreFlagsToString(int genreFlags) {
    std::string result;
    if (genreFlags & EGenreFlags::Action) result += "Action ";
    if (genreFlags & EGenreFlags::Comedy) result += "Comedy ";
    if (genreFlags & EGenreFlags::Drama) result += "Drama ";
    if (genreFlags & EGenreFlags::Horror) result += "Horror ";
    if (genreFlags & EGenreFlags::SciFi) result += "SciFi ";
    if (genreFlags & EGenreFlags::Romance) result += "Romance ";
    if (genreFlags & EGenreFlags::Documentary) result += "Documentary ";
    if (genreFlags & EGenreFlags::Thriller) result += "Thriller ";
    if (genreFlags & EGenreFlags::Crime) result += "Crime ";
    if (genreFlags & EGenreFlags::Fantasy) result += "Fantasy ";
    if (genreFlags & EGenreFlags::Animation) result += "Animation ";
    if (genreFlags & EGenreFlags::Adventure) result += "Adventure ";
    return result.empty() ? "None" : result;
}

class TMovie {
    std::string Title;
    std::string Director;
    int year;
    int genreFlags;
    float score;


    public:

        // Time: O(1) | Space: O(1)
        TMovie(const std::string& title, const std::string& director, int year, int genre, float score)
            : Title(title), Director(director), year(year), genreFlags(genre), score(score) {}

    // Time: O(1) (printing considered output-bound) | Space: O(1)
    void printInfo() {
        std::cout << "Title: " << Title << std::endl;
        std::cout << "Director: " << Director << std::endl;
        std::cout << "Year: " << year << std::endl;
        std::cout << "Genres: " << GenreFlagsToString(genreFlags) << std::endl;
        std::cout << "Score: " << score << std::endl;
    }
    // Time: O(1) | Space: O(1)
    std::string GetTitle() { return Title; }
    // Time: O(1) | Space: O(1)
    std::string GetDirector() { return Director; }
    // Time: O(1) | Space: O(1)
    int GetYear() { return year; }
    // Time: O(1) | Space: O(1)
    float getRating() { return score; }
    // Time: O(1) | Space: O(1)
    int GetGenreFlags() { return genreFlags; }
    // Time: O(1) | Space: O(1)
    bool hasGenre(EGenreFlags genre) {
        return (genreFlags & genre) != 0;
    }
};

typedef bool (*FCheckMovie)(TMovie*, void*);
// Make index callback void-returning since we don't use a return value
typedef void (*FMovieIndex)(TMovie*, int);


struct TMovieNode {
        TMovie* Movie;
        TMovieNode* Next;
        TMovieNode* Previous;
        // Time: O(1) | Space: O(1)
        TMovieNode(TMovie* movie): Movie(movie), Next(nullptr), Previous(nullptr) {}

    public:


        // Time: O(1) (TMovie destructor assumed O(1)) | Space: O(1)
        ~TMovieNode() {
            delete Movie;
        }

    // Time: O(1) | Space: O(1)
    TMovie* GetMovie() { return Movie; }
    // Time: O(1) | Space: O(1)
    TMovieNode* GetNext() { return Next; }
    // Time: O(1) | Space: O(1)
    TMovieNode* GetPrevious() { return Previous; }

    // Time: O(1) | Space: O(1)
    void SetNext(TMovieNode* next) { Next = next; }
    // Time: O(1) | Space: O(1)
    void SetPrevious(TMovieNode* previous) { Previous = previous; }
};


class TMovieList {
private:
    TMovieNode* Head;
    TMovieNode* Tail;
    int size;

    // Time: O(n) worst (up to n/2 traversals) | Space: O(1)
    TMovieNode* internalGetAtIndex(int index) {
        if (index < 0 || index >= size) {
            return nullptr;
        }
        TMovieNode* current;
        if (index < size / 2) {
            current = Head->Next;
            for (int i = 0; i < index; i++) {
                current = current->Next;
            }
        }
        else {
            current = Tail;
            for (int i = size - 1; i > index; i--) {
                current = current->Previous;
            }
        }
        return current;
    }

public:

    // Time: O(1) | Space: O(1)
    TMovieList() {
            Head = new TMovieNode(nullptr);
            Tail = Head;
            size = 0;

    }

    // Time: O(n) (calls Clear) | Space: O(1)
    ~TMovieList() {
        Clear();
        delete Head;
        }

    // Time: O(n) | Space: O(1)
    void Clear() {
        TMovieNode* Current = Head->Next;
        while (Current) {
            TMovieNode* toDelete = Current;
            Current = Current->Next;
            // Only delete the node; the node's destructor deletes the movie
            delete toDelete;
        }
        Head->Next = nullptr;
        Tail = Head;
        size = 0;
        }

    // Time: O(1) | Space: O(1)
    void append(TMovie* movie) {
        TMovieNode* newNode = new TMovieNode(movie);
        newNode->Previous = Tail;
        Tail->Next = newNode;
        Tail = newNode;
        size++;
    }

    // Time: O(1) | Space: O(1)
    void prepend(TMovie* movie) {
        TMovieNode* newNode = new TMovieNode(movie);
        newNode->Next = Head->Next;
        newNode->Previous = Head;
        if (Head->Next) {
            Head->Next->Previous = newNode;
        }
        else {
            Tail = newNode;
        }
        Head->Next = newNode;
        size++;
    }

    // Time: O(n) (depends on internalGetAtIndex) | Space: O(1)
    TMovie* GetAtIndex(int index) {
        TMovieNode* node = internalGetAtIndex(index);
        return node ? node->GetMovie() : nullptr;
    }

    // Time: O(n) (lookup) | Space: O(1)
    bool RemoveAtIndex(int aIndex) {
        if (aIndex < 0 || aIndex >= size) return false;
        TMovieNode* toDelete = internalGetAtIndex(aIndex);
        if (!toDelete) return false;
        if (toDelete->Previous) {
            toDelete->Previous->Next = toDelete->Next;
        } else {
            // Removing the first content node, update head's next
            Head->Next = toDelete->Next;
        }
        if (toDelete->Next) {
            toDelete->Next->Previous = toDelete->Previous ? toDelete->Previous : Head;
        } else {
            // Removing the last node, update Tail
            Tail = toDelete->Previous ? toDelete->Previous : Head;
        }
        delete toDelete; // Node destructor deletes Movie
        size--;
        return true;
    }

    // Time: O(n) | Space: O(1)
    void reverse() {
        if (size <= 1) return;
        TMovieNode* current = Head->Next;
        TMovieNode* prev = nullptr;
        TMovieNode* newTail = current;
        while (current) {
            TMovieNode* next = current->Next;
            current->Next = prev;
            current->Previous = next;
            prev = current;
            current = next;
        }
        // prev is the new first content node
        Head->Next = prev;
        if (prev) prev->Previous = Head;
        Tail = newTail ? newTail : Head;
    }

    // Time: O(n) worst-case | Space: O(1)
    TMovie* SearchFor(FCheckMovie aCheckFunc, void* aUserData) {
        TMovieNode* current = Head->Next;
        while (current) {
            if (aCheckFunc(current->Movie, aUserData)) {
                return current->Movie;
            }
            current = current->Next;
        }
        return nullptr;
    }

    // Time: O(n) | Space: O(1)
    void everyMovie(FMovieIndex aIndexFunc) {
        TMovieNode* current = Head->Next;
        int index = 0;
        while (current) {
            aIndexFunc(current->Movie, index);
            current = current->Next;
            index++;
        }
    }



};
// Time: O(1) (printing cost depends on string length) | Space: O(1)
static void printNode(std::string* data, int index) {
    std::cout << "Movie/node " << index << ": " << *data << std::endl;
}

// Time: O(L) where L = min(lengths of compared titles) | Space: O(1)
static bool checkMovieByTitle(TMovie* movie, void* title) {
    return movie->GetTitle() == *(static_cast<std::string*>(title));
}

// Time: O(L) where L = min(lengths of compared directors) | Space: O(1)
static bool checkMovieByDirector(TMovie* movie, void* director) {
    return movie->GetDirector() == *(static_cast<std::string*>(director));
}

// Time: O(1) (bit check + optional print) | Space: O(1)
static bool findAllMoviesByGenre(TMovie* movie, void* genre) {
    if (movie->hasGenre(*(static_cast<EGenreFlags*>(genre)))) {
        movie->printInfo();
        return true;
    }
    return false;
}

// Helper function for printing Action movies (non-capturing for function pointer compatibility)
// Time: O(1) (bit check + optional print) | Space: O(1)
static void PrintActionMovies(TMovie* movie, int /*index*/) {
    if (movie->hasGenre(EGenreFlags::Action)) {
        movie->printInfo();
        std::cout << "-------------------" << std::endl;
    }
}

// Time: O(n) overall (n = number of movies, fixed small here) | Space: O(1)
int main()
{

    std::cout << "--- Submission 1: Linked List ---" << std::endl;

    // Create a movie list
    TMovieList movieList;
    // Add some movies
    movieList.append(new TMovie("Inception", "Christopher Nolan", 2010, EGenreFlags::Action | EGenreFlags::SciFi, 8.8f));
    movieList.append(new TMovie("The Godfather", "Francis Ford Coppola", 1972, EGenreFlags::Crime | EGenreFlags::Drama, 9.2f));
    movieList.prepend(new TMovie("Toy Story", "John Lasseter", 1995, EGenreFlags::Animation | EGenreFlags::Adventure | EGenreFlags::Comedy, 8.3f));
    movieList.append(new TMovie("The Dark Knight", "Christopher Nolan", 2008, EGenreFlags::Action | EGenreFlags::Crime | EGenreFlags::Drama, 9.0f));
    // Print movie info
    for (int i = 0; i < 3; i++) {
        TMovie* movie = movieList.GetAtIndex(i);
        if (movie) {
            movie->printInfo();
            std::cout << "-------------------" << std::endl;
        }
    }
    std::cout << std::endl;
    // Wait for user input to proceed
    std::cout << "Press Enter to continue..." << std::endl;
    std::cin.get();

    // Search for a movie by title
    std::string searchTitle = "Inception";
    TMovie* foundMovie = movieList.SearchFor(checkMovieByTitle, &searchTitle);
    if (foundMovie) {
        std::cout << "Found movie by title '" << searchTitle << "':" << std::endl;
        foundMovie->printInfo();
    } else {
        std::cout << "Movie with title '" << searchTitle << "' not found." << std::endl;
    }


    // Search for a movie by director
    std::string searchDirector = "John Lasseter";
    foundMovie = movieList.SearchFor(checkMovieByDirector, &searchDirector);
    if (foundMovie) {
        std::cout << "Found movie by director '" << searchDirector << "':" << std::endl;
        foundMovie->printInfo();
    } else {
        std::cout << "Movie with director '" << searchDirector << "' not found." << std::endl;
    }
    std::cout << std::endl;

    // Find all movies in the Action genre
    std::cout << "Movies in the Action genre:" << std::endl;
    movieList.everyMovie(PrintActionMovies);
    std::cout << std::endl;

    // Reverse the list
    movieList.reverse();
    std::cout << "Movies after reversing the list:" << std::endl;
    movieList.everyMovie([](TMovie* movie, int index) {
        std::cout << "Index " << index << ":" << std::endl;
        movie->printInfo();
        });

    return 0;
}