#include <iostream>

enum EMovieGenreType {
    ACTION      = 1 << 0,
    COMEDY      = 1 << 1,
    SCIFI       = 1 << 2,
    HORROR      = 1 << 3,
    DRAMA       = 1 << 4
};

class TMovie {
    std::string Title;
    std::string Director;
    int year;
    EMovieGenreType Genre;
    float score;


    public:

        TMovie(const std::string& title, const std::string& director, int year, EMovieGenreType genre, float score)
            : Title(title), Director(director), year(year), Genre(genre), score(score) {}

    std::string GetTitle() { return Title; }
    std::string GetDirector() { return Director; }
    int GetYear() { return year; }
    EMovieGenreType GetGenre() { return Genre; }
    float GetScore() { return score; }

};

class TMovieNode {
        TMovie* Movie;
        TMovieNode* Next;
        TMovieNode* Previous;

    public:
        TMovieNode(TMovie* movie){
              Movie(movie), Next(nullptr);
        }

        ~TMovieNode() {
            delete Movie;
        }

    TMovie* GetMovie() { return Movie; }
    TMovieNode* GetNext() { return Next; }
    TMovieNode* GetPrevious() { return Previous; }

    void SetNext(TMovieNode* next) { Next = next; }
    void SetPrevious(TMovieNode* previous) { Previous = previous; }
};


class TMovieList {
    TMovieNode* Head;
    TMovieNode* Tail;
public:

    TMovieList() {
            Head = new TMovieNode(nullptr);
            Tail = new TMovieNode(nullptr);
    }

    ~TMovieList() {
            TMovieNode* current = Head;
            while (current != nullptr) {
                TMovieNode* Next = current->GetNext();
                delete current;
                current = Next;
            }
            Head = nullptr;
        }

    void append(TMovie* movie) {
            TMovieNode* newNode = new TMovieNode(movie);
            TMovieNode* current = Head;

            while (current->GetNext() != nullptr) {
                current = current->GetNext();
            }
            current->SetNext(newNode);
        }

    void prepend(TMovie* movie) {
        TMovieNode* newNode = new TMovieNode(movie);
            newNode->SetNext(Head->GetNext());
            Head->SetNext(newNode);
        }

    TMovieNode* GetAtIndex(int index) {
        TMovieNode* current = Head->GetNext();
        for (int i = 0; i < index && current != nullptr; i++) {
            current = current->GetNext();
        }
        return current;
    }

    void RemoveAtIndex(int index) {
        index = index - 1;
        TMovieNode* before = GetAtIndex(index);
        TMovieNode* ToDelete = before->GetNext();
        before->SetNext(ToDelete->GetNext());
        delete ToDelete;
    }

};

int main() {
    TMovieList MovieList;
    TMovie* m = new TMovie("Inception", "Christopher Nolan", 2010, (EMovieGenreType)(ACTION | SCIFI), 8.8f);
    TMovie* m2 = new TMovie("LOTR", "Navn navnesen", 2020, (EMovieGenreType)(ACTION | SCIFI), 8.8f);
    TMovie* m3 = new TMovie("Melkøya", "Kirsti Bergstø", 2025, (EMovieGenreType)(SCIFI), 2.5);
    MovieList.append(m);
    MovieList.append(m2);
    MovieList.append(m3);
    MovieList.RemoveAtIndex(2);
    std::cout << MovieList.GetAtIndex(0)->GetMovie()->GetTitle() << "movie1" << std::endl;
    std::cout << MovieList.GetAtIndex(1)->GetMovie()->GetTitle() << "movie2" << std::endl;
    std::cout << MovieList.GetAtIndex(2)->GetMovie()->GetTitle() << "movie3" << std::endl;
    return 0;
}

// TIP See CLion help at <a
// href="https://www.jetbrains.com/help/clion/">jetbrains.com/help/clion/</a>.
//  Also, you can try interactive lessons for CLion by selecting
//  'Help | Learn IDE Features' from the main menu.