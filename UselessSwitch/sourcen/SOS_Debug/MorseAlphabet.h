
const word K = 240;  // (240ms entsprechen25 BpM oder auch 5WpM)
const word L = 3 * K;
const word SYMBOL_PAUSE = K;
const word BUCHSTABEN_PAUSE = 3 * K;
const word WORT_PAUSE = 7 * K;
const word LOOP_PAUSE = 1000;

const word BUCHSTABE_A[] = {K, L, 0}; //A   · −
const word BUCHSTABE_B[] = {L, K, K, K, 0}; //B   − · · ·
const word BUCHSTABE_C[] = {L, K, L, K, 0}; //C   − · − ·
const word BUCHSTABE_D[] = {L, K, K, 0}; //D   − · ·
const word BUCHSTABE_E[] = {K, 0}; //E   ·
const word BUCHSTABE_F[] = {K, K, L, K, 0}; //F   · · − ·
const word BUCHSTABE_G[] = {L, L, K, 0}; //G   − − ·
const word BUCHSTABE_H[] = {K, K, K, K, 0}; //H   · · · ·
const word BUCHSTABE_I[] = {K, K, 0}; //I   · ·
const word BUCHSTABE_J[] = {K, L, L, L, 0}; //J   · − − −
const word BUCHSTABE_K[] = {L, K, L, 0}; //K   − · −
const word BUCHSTABE_L[] = {K, L, K, K, 0}; //L   · − · ·
const word BUCHSTABE_M[] = {L, L, 0}; //M   − −
const word BUCHSTABE_N[] = {L, K, 0}; //N   − ·
const word BUCHSTABE_O[] = {L, L, L, 0}; //O   − − −
const word BUCHSTABE_P[] = {K, L, L, K, 0}; //P   · − − ·
const word BUCHSTABE_Q[] = {L, L, K, L, 0}; //Q   − − · −
const word BUCHSTABE_R[] = {K, L, K, 0}; //R   · − ·
const word BUCHSTABE_S[] = {K, K, K, 0}; //S   · · ·
const word BUCHSTABE_T[] = {L, 0}; //T   −
const word BUCHSTABE_U[] = {K, K, L, 0}; //U   · · −
const word BUCHSTABE_V[] = {K, K, K, L, 0}; //V   · · · −
const word BUCHSTABE_W[] = {K, L, L, 0}; //W   · − −
const word BUCHSTABE_X[] = {L, K, K, L, 0}; //X   − · · −
const word BUCHSTABE_Y[] = {L, K, L, L, 0}; //Y   − · − −
const word BUCHSTABE_Z[] = {L, L, K, K, 0}; //Z   − − · ·

const word BUCHSTABE_1[] = {K, L, L, L, L, 0}; //1   · − − − −
const word BUCHSTABE_2[] = {K, K, L, L, L, 0}; //2   · · − − −
const word BUCHSTABE_3[] = {K, K, K, L, L, 0}; //3   · · · − −
const word BUCHSTABE_4[] = {K, K, K, K, L, 0}; //4   · · · · −
const word BUCHSTABE_5[] = {K, K, K, K, K, 0}; //5   · · · · ·
const word BUCHSTABE_6[] = {L, K, K, K, K, 0}; //6   − · · · ·
const word BUCHSTABE_7[] = {L, L, K, K, K, 0}; //7   − − · · ·
const word BUCHSTABE_8[] = {L, L, L, K, K, 0}; //8   − − − · ·
const word BUCHSTABE_9[] = {L, L, L, L, K, 0}; //9   − − − − ·
const word BUCHSTABE_0[] = {L, L, L, L, L, 0}; //0   − − − − −

