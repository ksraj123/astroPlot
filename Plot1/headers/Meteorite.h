class Meteorite {
    public:
        char* type;
        bool fallen;
        int id;
        int year;
        double mass;
        double longitude;
        double latitude;

        Meteorite(){}

        // Copy constructor
        Meteorite(const Meteorite *m) {
            this->type = m->type;
            this->fallen = m->fallen;
            this->id = m->id;
            this->year = m->year;
            this->mass = m->mass;
            this->longitude = m->longitude;
            this->latitude = m->latitude;
        }
};