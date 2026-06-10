#ifndef ARGS_HPP_019e30a4_a806_7801_adba_e71cacca2edc
#define ARGS_HPP_019e30a4_a806_7801_adba_e71cacca2edc
struct tallis_args
{
    unsigned int width {640}, height {480};
};

int tallis_args_parse(int, char**, tallis_args&);
#endif /* ARGS_HPP_019e30a4_a806_7801_adba_e71cacca2edc */
