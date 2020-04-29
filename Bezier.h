#ifndef BEZIER
#define BEZIER

#include <glm/glm.hpp>
#include <vector>

class Bezier{
public:
    float tRate;                       /**< Rate of change of t when drawing */
    std::vector<glm::vec2>curve;       /**< Points on the curve */
    std::vector<glm::vec2>controls;    /**< Control points */

    /**
     * Constructor
     * @param tRate rate of increase of t
     */
    Bezier(float tRate)
    {
        this->tRate = tRate;
    }

    /**
     * Linear Interpolation
     * @param a first point
     * @param b second point
     * @param t weight/baricentre parameter
     */
    glm::vec2 Lerp(glm::vec2 a, glm::vec2 b, float t)
    {
        return glm::vec2((1-t)*(a.x) + t*(b.x), (1-t)*(a.y) + t*(b.y));
    }

    /**
     * Make a point using the De Casteljau's Algorithm
     * @param start starting control point
     * @param end ending control point
     * @param t parameter
     * @return point on the curve
     */
    glm::vec2 DeCasteljau(int start, int end, float t)
    {
        std::vector <glm::vec2> temp; 
        if(start == end) return this->controls[start];
        int dif = end - start;
        for(int i = start; i<=end; i++) temp.push_back(this->controls[i]);

        for(int i=0; i<dif; i++)
        {
            // Linear interpolations
            for(int j=0; j<temp.size()-1; j++)
            {
                temp[j] = this->Lerp(temp[j], temp[j+1], t);
            }
            temp.pop_back();
        }
        return temp[0];
    }

    /**
     * Add point and redraw curve using De Casteljau's algo
     * @param pos position of new point
     * @see DeCasteljau()
     */
    void newPoint(glm::vec2 pos)
    {
        this->controls.push_back(pos);
        if(this->controls.size() == 1)
        {
            float t = 0.0;
            while(t <= 1.0)
            {
                this->curve.push_back(this->controls[0]);
                t += this->tRate;
            }
        }
        else
        {
            int point = 0;
            float t = 0.0;
            int sz = this->controls.size();
            while(t <= 1.0)
            {
                this->curve[point] = this->Lerp(this->curve[point], this->DeCasteljau(1, sz-1, t), t);
                t += this->tRate;
                point++;
            }
        }
    }
    /**
     * Delete a control point and redraw using De Casteljau's algo
     * @param id index of the point in the controls vector.
     */
    void deletePoint(int id)
    {
        if(id < this->controls.size() && id >=0)
        {
            this->controls.erase(this->controls.begin() + id);
            this->curve.clear();
            if(controls.size() != 0)
            {
                this->redraw(0);
            }
        }
    }
    /**
     * Function to handle changina a control point and redraw
     * @param id index of the point in the controls vector
     * @param pos new position
     */
    void movePoint(int id, glm::vec2 pos)
    {
        if(id < this->controls.size())
        {
            this->controls[id] = pos;
            this->curve.clear();
            this->redraw(0);
        }
    }
    /**
     * Helper function to redraw after any changes
     * @param start starting index of the curve vector from where the drawing should start
     */
    void redraw(int start)
    {
        float t = 0.0;
        while(t <= 1.0)
        {
            glm::vec2 point = this->DeCasteljau(start, this->controls.size()-1, t);
            this->curve.push_back(point);
            t += this->tRate;
        }
    }
};

#endif