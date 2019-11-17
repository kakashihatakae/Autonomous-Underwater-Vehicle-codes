class Storage
{
    public:
    int NUM_ACTUATORS;
    float PERIOD;
    float UWSIM_PERIOD;
    float MASS;
    float GRAVITY_CENTRE[3];
    float G;
    float RADIUS;

    //coriolis
    double cTF ;
    double cTB ;

    //actuators
    float ACTUATORS_TAU[5];
    int ACUATORS_MAX_SAT[5];
    int ACTUATORS_MIN_SAT[5];
    int ACTUATORS_GAIN[5];
    
    float DZV;
    float DV;
    float DH;
    float DENSITY;

    //damping 
    float TENSOR[9];
    float DAMPING[6];
    float QUAD_DAMPING[6];

    //mass
    float MRB[6][6];
    float MA[6][6];

    //================================
    float ALLOCATION_MATRIX;
    //================================

    float INITIAL_POSE[6];
    float INITIAL_VELOCITY;
    Storage();


};
