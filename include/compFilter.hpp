#ifndef COMP_FILTER_HPP
#define COMP_FILTER_HPP

class compFilter
{
    private:
        float alpha;
        float y;

    public:
        void update(const float& x);
        const float getY();

};

#endif // COMP_FILTER_HPP