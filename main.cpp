#include <iostream>
#include <utility>
#include <vector>

class Crew {
    std::string name;
    int age = 30;

public:
    /// constructor + destructor
    Crew(){std::cout << "Constructor Crew\n";}
    Crew(std::string  name_, int age_) : name{std::move(name_)}, age{age_} { std::cout << "Constructor Crew\n";}
    ~Crew() {std::cout << "Destructor Crew\n";}

    /// get si set
    [[nodiscard]]const std::string& get_name() const { return name; }
    //[[nodiscard]]int get_age() const { return age; }
    //void set_name(const std::string& name_) { this->name = name_; }
    //void set_age(int age_) { this->age = age_; }

    /// cc
    Crew(const Crew& other) : name{other.name}, age{other.age} {std::cout << "cc Crew\n";}

    /// operator=
    Crew& operator=(const Crew& other) {
        this->name = other.name;
        this->age = other.age;
        std::cout << "operator= Crew\n";
        return *this;
    }

    ///operator<<
    friend std::ostream& operator<<(std::ostream& os, const Crew& crew) {
        os << "Nume: " << crew.name << ", varsta: " << crew.age;
        return os;
    }
};



class Review {
    double rating = 3;
    std::string content;

public:
    /// constructor + destructor
    Review() {std::cout << "Constructor Review\n";}
    Review(double rating_, std::string  content_) : rating{rating_}, content{std::move(content_)} {}
    ~Review() {std::cout << "Destructor Review\n";}

    /// get si set
    [[nodiscard]]double get_rating() const { return rating; }
    [[nodiscard]]const std::string& get_content() const { return content; }
    //void set_rating(double rating_) { this->rating = rating_; }
    //void set_content(const std::string& content_) { this->content = content_; }

    /// cc
    Review(const Review& other) : rating{other.rating}, content{other.content} { std::cout << "cc Review\n";}

    /// operator=
    Review& operator=(const Review& other) {
        this->rating = other.rating;
        this->content = other.content;
        std::cout << "operator= Review\n";
        return *this;
    }

    ///operator<<
    friend std::ostream& operator<<(std::ostream& os, const Review& review) {
        os << "Rating: " << review.rating << "\n" << review.content;
        return os;
    }
};



class Film {
    std::string film_name;
    int release_year = 2000;
    Crew director;
    std::vector<std::string> genres;
    int runtime = 120;

    std::string synopsis;
    std::vector<Crew> cast;
    std::vector<Review> reviews;
    double average_rating = 3;

public:
    /// constructor + destructor
    Film() {std::cout << "Constructor Film\n";}
    //Film(const std::string& film_name_) : film_name{film_name_} {std::cout << "Constructor Film1\n";}
    Film(std::string  film_name_, int release_year_, const Crew& director_, const std::vector<std::string>& genres_,
         int runtime_, std::string  synopsis_, const std::vector<Crew>& cast_,
         const std::vector<Review>& reviews_, double average_rating_) : film_name{std::move(film_name_)},
                                                                        release_year{release_year_}, director{director_}, genres{genres_}, runtime{runtime_}, synopsis{std::move(synopsis_)},
                                                                        cast{cast_}, reviews{reviews_}, average_rating{average_rating_} {}
    ~Film() {std::cout << "Destructor Film\n";}

    /// get si set
    [[nodiscard]]const std::string& get_film_name() const { return film_name; }
    [[nodiscard]]int get_release_year() const { return release_year; }
    [[nodiscard]]const Crew& get_director() const { return director; }
    [[nodiscard]]const std::vector<std::string>& get_genres() const { return genres; }
    [[nodiscard]]int get_runtime() const { return runtime; }
    [[nodiscard]]const std::string& get_synopsis() const { return synopsis; }
    [[nodiscard]]const std::vector<Crew>& get_cast() const { return cast; }
    [[nodiscard]]const std::vector<Review>& get_reviews() const { return reviews; }
    [[nodiscard]]double get_average_rating() const { return average_rating; }
    //void set_film_name(const std::string& film_name_) { this->film_name = film_name_; }
    //void set_release_year(int release_year_) { this->release_year = release_year_; }
    //void set_director(const Crew& director_) { this->director = director_; }
    //void set_genres(const std::vector<std::string>& genres_) { this->genres = genres_; }
    //void set_runtime(int runtime_) { this->runtime = runtime_; }
    //void set_synopsis(const std::string& synopsis_) { this->synopsis = synopsis_; }
    //void set_cast(const std::vector<Crew>& cast_) { this->cast = cast_; }
    //void set_reviews(const std::vector<Review>& reviews_) { this->reviews = reviews_; }
    //void set_average_rating(double average_rating_) { this->average_rating = average_rating_; }

    /// cc
    Film(const Film& other) : film_name{other.film_name}, release_year{other.release_year}, director{other.director},
                              genres{other.genres}, runtime{other.runtime}, synopsis{other.synopsis}, cast{other.cast},
                              reviews{other.reviews}, average_rating{other.average_rating} {std::cout << "cc Film\n";}

    /// operator=
    Film& operator=(const Film& other) {
        this->film_name = other.film_name;
        this->release_year = other.release_year;
        this->director = other.director;
        this->genres = other.genres;
        this->runtime = other.runtime;
        this->synopsis = other.synopsis;
        this->cast = other.cast;
        this->reviews = other.reviews;
        this->average_rating = other.average_rating;
        std::cout << "operator= Film\n";
        return *this;
    }

    ///operator<<
    friend std::ostream& operator<<(std::ostream& os, const Film& film) {
        os << "Film: " << film.film_name << ", anul aparitiei: " << film.release_year << ", regizor: " << film.director << "\n";
        os << "Genuri: ";
        for (const auto& genre : film.genres) {
            os << genre << " ";
        }
        os << "\n";
        os << "Durata: " << film.runtime << "\n";
        os << "Sinopsis: " << film.synopsis << "\n";
        os << "Distributie:\n";
        for (const auto& actor : film.cast) {
            os << actor << " ";
        }
        os << "\n";
        os << "Recenzii populare:\n";
        for (const auto& review : film.reviews) {
            os << review << " ";
        }
        os << "\n";
        os << "Rating mediu: " << film.average_rating;
        return os;
    }

    void update_average_rating() {
        double sum = 0;
        for (const auto& review : reviews) {
            sum += review.get_rating();
        }
        average_rating = sum / (1.0 * (double)reviews.size());
    }

    void add_review(const Review& review) {
        reviews.push_back(review);
        update_average_rating();
    }
};



class Library {
    std::vector< std::pair <Film, Review> > watched_films;

public:
    /// constructor + destructor
    Library() { watched_films.clear(); std::cout << "Constructor Library\n"; }
    explicit Library(const std::vector< std::pair <Film, Review> >& watched_films_) : watched_films{watched_films_} { std::cout << "Constructor1 Library\n"; }
    ~Library() { std::cout << "Destructor Library\n"; }

    /// get si set
    [[nodiscard]]const std::vector< std::pair <Film, Review> >& get_watched_films() const { return watched_films; }
    //void set_watched_films(const std::vector< std::pair <Film, Review> >& watched_films_)
    //{ this->watched_films = watched_films_; }

    /// cc
    Library(const Library& other) : watched_films{other.watched_films} { std::cout << "cc Library\n"; }

    /// operator=
    /*Library& operator=(const Library& other) {
        this->watched_films = other.watched_films;
        std::cout << "operator= Library\n";
        return *this;
    }*/
    Library& operator=(const Library& other) = default;

    ///operator<<
    friend std::ostream& operator<<(std::ostream& os, const Library& library) {
        os << "Filmele vizionate: ";
        for (const auto& film : library.watched_films) {
            os << film.first << " " << film.second << "\n";
        }
        return os;
    }

    void add_film(const Film& film, const Review& review) {
        watched_films.emplace_back(film, review);
    }

    void remove_film(const Film& film) {
        for (auto it = watched_films.begin(); it != watched_films.end(); it++) {
            if (it->first.get_film_name() == film.get_film_name()) {
                watched_films.erase(it);
                break;
            }
        }
    }

    void update_film(const Film& film, const Review& review) {
        /// auto &[film, review]
        for (auto & watched_film : watched_films) {
            if (watched_film.first.get_film_name() == film.get_film_name()) {
                watched_film.first = film;
                watched_film.second = review;
                break;
            }
        }
    }

    ///search functions
    const Film& search_film_name(const std::string& film_name) {
        for (auto& film : watched_films) {
            if (film.first.get_film_name() == film_name) {
                return film.first;
            }
        }
        static Film film_not_found("not found", 0, Crew("not found", 0), std::vector<std::string>{}, 0, "not found", std::vector<Crew>{}, std::vector<Review>{}, 0);
        return film_not_found;
        //Film film_not_found("not found");
        //return film_not_found;
    }

    const Film& search_film_director(const std::string& director) {
        for (auto& film : watched_films) {
            if (film.first.get_director().get_name() == director) {
                return film.first;
            }
        }
        static Film film_not_found("not found", 0, Crew("not found", 0), std::vector<std::string>{}, 0, "not found", std::vector<Crew>{}, std::vector<Review>{}, 0);
        return film_not_found;
        //Film film_not_found("not found");
        //return film_not_found;
    }

    const Film& search_film_actor(const std::string& actor) {
        for (auto& film : watched_films) {
            for (auto& participant_actor : film.first.get_cast()) {
                if (participant_actor.get_name() == actor) {
                    return film.first;
                }
            }
        }
        static Film film_not_found("not found", 0, Crew("not found", 0), std::vector<std::string>{}, 0, "not found", std::vector<Crew>{}, std::vector<Review>{}, 0);
        return film_not_found;
        //Film film_not_found("not found");
        //return film_not_found;
    }

    const Film& search_film_year(const int& year) {
        for (auto& film : watched_films) {
            if (film.first.get_release_year() == year) {
                return film.first;
            }
        }
        static Film film_not_found("not found", 0, Crew("not found", 0), std::vector<std::string>{}, 0, "not found", std::vector<Crew>{}, std::vector<Review>{}, 0);
        return film_not_found;
    }

    static bool cmp(const std::pair <Film, Review>& w1, const std::pair <Film, Review>& w2) {
        return w1.second.get_rating() > w2.second.get_rating();
    }

    void sort_rating() {
        sort(watched_films.begin(), watched_films.end(), cmp);
    }

};



/*class Film_List {
    std::vector<Film> films;
    std::string description;

public:
    /// constructor + destructor
    Film_List() {std::cout << "constructor film_list\n";}
    Film_List(const std::vector<Film>& films_, const std::string& description_) : films{films_},
        description{description_} {}
    ~Film_List() {std::cout << "destructor film_list\n";}

    /// get si set
    [[nodiscard]]const std::vector<Film>& get_films() const { return films; }
    [[nodiscard]]const std::string& get_description() const { return description; }
    //void set_films(const std::vector<Film>& films_) { this->films = films_; }
    //void set_description(const std::string& description_) { this->description = description_; }

    /// cc
    Film_List(const Film_List& other) : films{other.films}, description{other.description} { std::cout << "cc film_list\n";}

    /// operator=
    Film_List& operator=(const Film_List& other) {
        this->films = other.films;
        this->description = other.description;
        std::cout << "operator= film_list\n";
        return *this;
    }

    /// operator<<
    friend std::ostream& operator<<(std::ostream& os, const Film_List& film_list) {
        os << "Descriere: " << film_list.description << "\n" << "Filme: ";
        for (const auto& film : film_list.films) {
            os << film << " ";
        }
        return os;
    }

};*/

/*
class Watchlist {
    std::vector<Film> films;

public:
    /// constructor + destructor
    Watchlist() {}
    Watchlist(const std::vector<Film>& films_) : films{films_} {}
    ~Watchlist() {}

    /// get si set
    const std::vector<Film>& get_films() const { return films; }
    void set_films(const std::vector<Film>& films_) { this->films = films_; }

    /// cc
    Watchlist(const Watchlist& other) : films{other.films} {}

    /// operator=
    Watchlist& operator=(const Watchlist& other) {
        this->films = other.films;
        return *this;
    }

    /// operator<<
    friend std::ostream& operator<<(std::ostream& os, const Watchlist& watchlist) {
        os << "Filme de vizionat: ";
        for (const auto& film : watchlist.films) {
            os << film << " ";
        }
        return os;
    }
};
*/

/*
class Client {
    std::string name;
    std::string username;
    std::string password;

    Library library;
    Watchlist watchlist;
    std::vector<Film> fave_films;

public:
    /// constructor + destructor
    Client() {}
    Client(const std::string& name_, const std::string& username_, const std::string& password_, const Library& library_,
           const Watchlist& watchlist_, std::vector<Film>& fave_films_) : name{name_},
           username{username_}, password{password_}, library{library_}, watchlist{watchlist_},
           fave_films{fave_films_} {}
    ~Client() {}

    /// get si set
    const std::string& get_name() const { return name; }
    const std::string& get_username() const { return username; }
    const std::string& get_password() const { return password; }
    const std::vector<Film>& get_fave_films() const { return fave_films; }
    const Library& get_library() const { return library; }
    const Watchlist& get_watchlist() const { return watchlist; }
    void set_name(const std::string& name_) { this->name = name_; }
    void set_username(const std::string& username_) { this->username = username_; }
    void set_password(const std::string& password_) { this->password = password_; }
    void set_fave_films(const std::vector<Film>& fave_films_) { this->fave_films = fave_films_; }
    void set_library(const Library& library_) { this->library = library_; }
    void set_watchlist(const Watchlist& watchlist_) { this->watchlist = watchlist_; }

    /// cc
    Client(const Client& other) : name{other.name}, username{other.username}, password{other.password},
        fave_films{other.fave_films}, library{other.library}, watchlist{other.watchlist} {}

    /// operator=
    Client& operator=(const Client& other) {
        this->name = other.name;
        this->username = other.username;
        this->password = other.password;
        this->fave_films = other.fave_films;
        this->library = other.library;
        this->watchlist = other.watchlist;
        return *this;
    }

    /// operator<<
    friend std::ostream& operator<<(std::ostream& os, const Client& client) {
        os << "Nume: " << client.name << "\n" << "Username: " << client.username << "\n" << "Parola: " << client.password
        << "\n" << "Filme favorite: ";
        for (const auto& film : client.fave_films) {
            os << film << " ";
        }
        os << "\n" << "Biblioteca: " << client.library << "\n" << "Watchlist: " << client.watchlist;
        return os;
    }

};
*/



int main() {

    Crew LD("Leonardo DiCaprio", 48);
    Crew JH("Jonah Hill", 39);
    Crew MS("Martin Scorsese", 80);
    std::cout << MS << "\n";

    Crew BP("Brad Pitt", 59);
    Crew EN("Edward Norton", 53);
    Crew DF("David Fincher", 60);

    Review r1(4.5, "Great movie! I enjoyed it!");
    std::cout << r1 << "\n";
    Review r2(5, "Amazing! I'm gonna be the same as him!");
    Review r3(3.5, "It was ok, but I expected more from it. The book was better.");
    //Review r4(r1), r5 = r4;

    /*
     Film(const std::string& film_name_, int release_year_, const Crew& director_, const std::vector<std::string>& genres_,
         int runtime_, const std::string& synopsis_, const std::vector<Crew>& cast_,
         const std::vector<Review>& reviews_, double average_rating_) : film_name{film_name_},
         release_year{release_year_}, director{director_}, genres{genres_}, runtime{runtime_}, synopsis{synopsis_},
         cast{cast_}, reviews{reviews_}, average_rating{average_rating_} {}
     */

    std::vector<std::string> genres1{"Biography", "Crime", "Drama"};
    std::vector<Crew> cast1{LD, JH};
    std::vector<Review> reviews1{r1};
    std::cout << reviews1[0].get_rating() << "\n";
    std::string synopsis1 = "Based on the true story of Jordan Belfort, from his rise to a wealthy stock-broker living the high life to his fall involving crime, corruption and money laundering.";
    Film WOWS("Wolf of Wall Street", 2013, MS, genres1, 180, synopsis1, cast1, reviews1, 4.5);

    for (const auto& genre : WOWS.get_genres()) {
        std::cout << genre << " ";
    }
    std::cout << "\n";
    std::cout << WOWS.get_synopsis() << "\n" << WOWS.get_runtime() << "\n" << WOWS.get_average_rating() << "\n";
    for (const auto& review : WOWS.get_reviews()) {
        std::cout << review.get_rating() << " " << review.get_content() << "\n";
    }
    std::cout << "\n";
    std::cout << WOWS << "\n";


    std::vector<std::string> genres2{"Drama", "Thriller"};
    std::vector<Crew> cast2{BP, EN};
    std::vector<Review> reviews2{r2};
    std::string synopsis2 = "Unhappy with his capitalistic lifestyle, a white-collared insomniac forms an underground fight club with Tyler, a careless soap salesman. Soon, their venture spirals down into something sinister.";
    Film FC("Fight Club", 1999, DF, genres2, 139, synopsis2, cast2, reviews2, 5);
    FC.add_review(r3);
    std::cout << FC.get_average_rating() << "\n";

    std::vector< std::pair<Film, Review> > watched_film1{{WOWS, r1}};
    Library l1(watched_film1);
    Library l2 = l1;
    l1 = l2;
    std::cout << l2 << "\n";
    for (const auto& watched_film : l1.get_watched_films()) {
        std::cout << watched_film.first.get_film_name() << " " << watched_film.second.get_rating() << "\n";
    }
    l1.add_film(FC, r2);
    l1.sort_rating();
    std::cout << l1 << "\n";
    l1.remove_film(WOWS);
    l1.update_film(FC, r3);
    std::cout << l1.search_film_actor("Leonardo DiCaprio").get_film_name() << "\n";
    std::cout << l1.search_film_name("Fight Club").get_film_name() << "\n";
    std::cout << l1.search_film_year(2013).get_film_name() << "\n";
    std::cout << l1.search_film_director("David Fincher").get_film_name() << "\n";

    return 0;
}
