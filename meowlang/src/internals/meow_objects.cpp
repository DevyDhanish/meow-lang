#include "../../../include/internals/mewcore_obj.hpp"
#include <string>

/*
**************************************************************************************
*                                                                                    *   
*                       FOR INTEGER                                                  *
*                                                                                    * 
*                                                                                    *
**************************************************************************************
*/

void *Integer::onAdd(MeowObject *b) 
{
    switch(b->getKind())
    {
        case MEOWOBJECTKIND::IntObj:
        {
            Integer *newVal = new Integer((((Integer *)b)->value + value), MEOWOBJECTKIND::IntObj);
            return newVal;
            break;
        }
        case MEOWOBJECTKIND::FloatObj:
        {
            Float *newVal = new Float((((Float *)b)->value + value), MEOWOBJECTKIND::FloatObj);
            return newVal;
            break;
        }
        case MEOWOBJECTKIND :: StringObj:
        {
            std::cout << "Cannot add type<Integer> to type<String>\n";
            return NULL;
            break;
        }
        default:
        {
            std::cout << "Unknow MeowObj was passed\n";
            return NULL;
            break;
        }
    }
}

void *Integer::onSub(MeowObject *b)
{
    switch(b->getKind())
    {
        case MEOWOBJECTKIND::IntObj:
        {
            Integer *newVal = new Integer((((Integer *)b)->value - value), MEOWOBJECTKIND::IntObj);
            return newVal;
            break;
        }
        case MEOWOBJECTKIND::FloatObj:
        {
            Float *newVal = new Float((((Float *)b)->value - value), MEOWOBJECTKIND::FloatObj);
            return newVal;
            break;
        }
        case MEOWOBJECTKIND :: StringObj:
        {
            std::cout << "Cannot substract type<Integer> to type<String>\n";
            return NULL;
            break;
        }
        default:
        {
            std::cout << "Unknow MeowObj was passed\n";
            return NULL;
            break;
        }
    }
}

void *Integer::onMul(MeowObject *b)
{
    switch(b->getKind())
    {
        case MEOWOBJECTKIND::IntObj:
        {
            Integer *newVal = new Integer((((Integer *)b)->value * value), MEOWOBJECTKIND::IntObj);
            return newVal;
            break;
        }
        case MEOWOBJECTKIND::FloatObj:
        {
            Float *newVal = new Float((((Float *)b)->value * value), MEOWOBJECTKIND::FloatObj);
            return newVal;
            break;
        }
        case MEOWOBJECTKIND :: StringObj:
        {
            std::cout << "Cannot multiply type<Integer> to type<String>\n";
            return NULL;
            break;
        }
        default:
        {
            std::cout << "Unknow MeowObj was passed\n";
            return NULL;
            break;
        }
    }
}

void *Integer::onDiv(MeowObject *b)
{
    switch(b->getKind())
    {
        case MEOWOBJECTKIND::IntObj:
        {
            Float *newVal = new Float((((Integer *)b)->value / value), MEOWOBJECTKIND::FloatObj);
            return newVal;
            break;
        }
        case MEOWOBJECTKIND::FloatObj:
        {
            Float *newVal = new Float((((Float *)b)->value / value), MEOWOBJECTKIND::FloatObj);
            return newVal;
            break;
        }
        case MEOWOBJECTKIND :: StringObj:
        {
            std::cout << "Cannot divide type<Integer> to type<String>\n";
            return NULL;
            break;
        }
        default:
        {
            std::cout << "Unknow MeowObj was passed\n";
            return NULL;
            break;
        }
    }
}

void *Integer::onMod(MeowObject *b)
{
    switch(b->getKind())
    {
        case MEOWOBJECTKIND::IntObj:
        {
            Integer *newVal = new Integer((((Integer *)b)->value % value), MEOWOBJECTKIND::IntObj);
            return newVal;
            break;
        }
        // this ( / ) is just a place holder needs to be changed with %
        case MEOWOBJECTKIND::FloatObj:
        {
            Float *newVal = new Float((((Float *)b)->value / value), MEOWOBJECTKIND::FloatObj);
            return newVal;
            break;
        }
        case MEOWOBJECTKIND :: StringObj:
        {
            std::cout << "Cannot mod type<Integer> to type<String>\n";
            return NULL;
            break;
        }
        default:
        {
            std::cout << "Unknow MeowObj was passed\n";
            return NULL;
            break;
        }
    }
}

void *Integer::onCmpE(MeowObject *b)
{
    switch(b->getKind())
    {
        case MEOWOBJECTKIND::IntObj:
        {
            Integer *newVal = new Integer(( ((Integer *)b)->value == value ), MEOWOBJECTKIND::IntObj);
            return newVal;
            break;
        }
        // this ( / ) is just a place holder needs to be changed with %
        case MEOWOBJECTKIND::FloatObj:
        {
            Float *newVal = new Float(( ((Float *)b)->value == value ), MEOWOBJECTKIND::FloatObj);
            return newVal;
            break;
        }
        case MEOWOBJECTKIND :: StringObj:
        {
            std::cout << "Cannot `==` between type<Integer> to type<String>\n";
            return NULL;
            break;
        }
        default:
        {
            std::cout << "Unknow MeowObj was passed\n";
            return NULL;
            break;
        }
    }
}

void *Integer::onCmpNE(MeowObject *b)
{
    switch(b->getKind())
    {
        case MEOWOBJECTKIND::IntObj:
        {
            Integer *newVal = new Integer(( ((Integer *)b)->value != value ), MEOWOBJECTKIND::IntObj);
            return newVal;
            break;
        }
        // this ( / ) is just a place holder needs to be changed with %
        case MEOWOBJECTKIND::FloatObj:
        {
            Integer *newVal = new Integer(( ((Float *)b)->value != value ), MEOWOBJECTKIND::IntObj);
            return newVal;
            break;
        }
        case MEOWOBJECTKIND :: StringObj:
        {
            std::cout << "Cannot `!=` between type<Integer> to type<String>\n";
            return NULL;
            break;
        }
        default:
        {
            std::cout << "Unknow MeowObj was passed\n";
            return NULL;
            break;
        }
    }
}

void *Integer::onCmpL(MeowObject *b)
{
    switch(b->getKind())
    {
        case MEOWOBJECTKIND::IntObj:
        {
            Integer *newVal = new Integer(( ((Integer *)b)->value < value ), MEOWOBJECTKIND::IntObj);
            return newVal;
            break;
        }
        // this ( / ) is just a place holder needs to be changed with %
        case MEOWOBJECTKIND::FloatObj:
        {
            Integer *newVal = new Integer(( ((Float *)b)->value < value ), MEOWOBJECTKIND::IntObj);
            return newVal;
            break;
        }
        case MEOWOBJECTKIND :: StringObj:
        {
            std::cout << "Cannot `<` between type<Integer> to type<String>\n";
            return NULL;
            break;
        }
        default:
        {
            std::cout << "Unknow MeowObj was passed\n";
            return NULL;
            break;
        }
    }
}

void *Integer::onCmpLE(MeowObject *b)
{
    switch(b->getKind())
    {
        case MEOWOBJECTKIND::IntObj:
        {
            Integer *newVal = new Integer(( ((Integer *)b)->value <= value ), MEOWOBJECTKIND::IntObj);
            return newVal;
            break;
        }
        // this ( / ) is just a place holder needs to be changed with %
        case MEOWOBJECTKIND::FloatObj:
        {
            Integer *newVal = new Integer(( ((Float *)b)->value <= value ), MEOWOBJECTKIND::IntObj);
            return newVal;
            break;
        }
        case MEOWOBJECTKIND :: StringObj:
        {
            std::cout << "Cannot `<=` between type<Integer> to type<String>\n";
            return NULL;
            break;
        }
        default:
        {
            std::cout << "Unknow MeowObj was passed\n";
            return NULL;
            break;
        }
    }
}

void *Integer::onCmpG(MeowObject *b)
{
    switch(b->getKind())
    {
        case MEOWOBJECTKIND::IntObj:
        {
            Integer *newVal = new Integer(( ((Integer *)b)->value > value ), MEOWOBJECTKIND::IntObj);
            return newVal;
            break;
        }
        // this ( / ) is just a place holder needs to be changed with %
        case MEOWOBJECTKIND::FloatObj:
        {
            Integer *newVal = new Integer(( ((Float *)b)->value > value ), MEOWOBJECTKIND::IntObj);
            return newVal;
            break;
        }
        case MEOWOBJECTKIND :: StringObj:
        {
            std::cout << "Cannot `>` between type<Integer> to type<String>\n";
            return NULL;
            break;
        }
        default:
        {
            std::cout << "Unknow MeowObj was passed\n";
            return NULL;
            break;
        }
    }
}

void *Integer::onCmpGE(MeowObject *b)
{
    switch(b->getKind())
    {
        case MEOWOBJECTKIND::IntObj:
        {
            Integer *newVal = new Integer(( ((Integer *)b)->value >= value ), MEOWOBJECTKIND::IntObj);
            return newVal;
            break;
        }
        // this ( / ) is just a place holder needs to be changed with %
        case MEOWOBJECTKIND::FloatObj:
        {
            Integer *newVal = new Integer(( ((Float *)b)->value >= value ), MEOWOBJECTKIND::IntObj);
            return newVal;
            break;
        }
        case MEOWOBJECTKIND :: StringObj:
        {
            std::cout << "Cannot `>=` between type<Integer> to type<String>\n";
            return NULL;
            break;
        }
        default:
        {
            std::cout << "Unknow MeowObj was passed\n";
            return NULL;
            break;
        }
    }
}

void *Integer::onNegate()
{
    Integer *newVal = new Integer( -value, MEOWOBJECTKIND::IntObj);
    return newVal;
}

void *Integer::onAnd(MeowObject *b)
{
    return new Integer( ((Integer *)b)->value && value , MEOWOBJECTKIND::IntObj);
}

void *Integer::onOr(MeowObject *b)
{
    return new Integer( ((Integer *)b)->value || value , MEOWOBJECTKIND::IntObj);
}

/*
**************************************************************************************
*                                                                                    *   
*                       FOR STRING                                                   *
*                                                                                    * 
*                                                                                    *
**************************************************************************************
*/

void *String::onAdd(MeowObject *b)
{
    switch(b->getKind())
    {
        case MEOWOBJECTKIND::IntObj:
        {
            std::cout << "Cannon add type<Integer> to type<String>\n";
            return NULL;
            break;
        }
        case MEOWOBJECTKIND::FloatObj:
        {
            std::cout << "Cannot add type<Float> to type<String>\n";
            return NULL;
            break;
        }
        case MEOWOBJECTKIND :: StringObj:
        {
            String *newVal = new String((((String *)b)->value + value), MEOWOBJECTKIND::StringObj);
            return newVal;
            break;
        }
        default:
        {
            std::cout << "Unknow MeowObj was passed\n";
            return NULL;
            break;
        }
    }
}

void *String::onSub(MeowObject *b)
{
    switch(b->getKind())
    {
        case MEOWOBJECTKIND::IntObj:
        {
            std::cout << "Cannon substrace type<Integer> to type<String>\n";
            return NULL;
            break;
        }
        case MEOWOBJECTKIND::FloatObj:
        {
            std::cout << "Cannot substrace type<Float> to type<String>\n";
            return NULL;
            break;
        }
        case MEOWOBJECTKIND :: StringObj:
        {
            std::cout << "Cannot substract type<String> to type<String>\n";
            return NULL;
            break;
        }
        default:
        {
            std::cout << "Unknow MeowObj was passed\n";
            return NULL;
            break;
        }
    }
}

void *String::onMul(MeowObject *b)
{
    switch(b->getKind())
    {
        case MEOWOBJECTKIND::IntObj:
        {
            std::cout << "Cannon multiply type<Integer> to type<String>\n";
            return NULL;
            break;
        }
        case MEOWOBJECTKIND::FloatObj:
        {
            std::cout << "Cannot multiply type<Float> to type<String>\n";
            return NULL;
            break;
        }
        case MEOWOBJECTKIND :: StringObj:
        {
            std::cout << "Cannot multiplay type<String> to type<String>\n";
            return NULL;
            break;
        }
        default:
        {
            std::cout << "Unknow MeowObj was passed\n";
            return NULL;
            break;
        }
    }
}

void *String::onDiv(MeowObject *b)
{
    switch(b->getKind())
    {
        case MEOWOBJECTKIND::IntObj:
        {
            std::cout << "Cannon div type<Integer> to type<String>\n";
            return NULL;
            break;
        }
        case MEOWOBJECTKIND::FloatObj:
        {
            std::cout << "Cannot div type<Float> to type<String>\n";
            return NULL;
            break;
        }
        case MEOWOBJECTKIND :: StringObj:
        {
            std::cout << "Cannot divide type<String> to type<String>\n";
            return NULL;
            break;
        }
        default:
        {
            std::cout << "Unknow MeowObj was passed\n";
            return NULL;
            break;
        }
    }
}

void *String::onMod(MeowObject *b)
{
    switch(b->getKind())
    {
        case MEOWOBJECTKIND::IntObj:
            std::cout << "Cannon add type<Integer> to type<String>\n";
            return NULL;
            break;
        case MEOWOBJECTKIND::FloatObj:
            std::cout << "Cannot add type<Float> to type<String>\n";
            return NULL;
            break;
        case MEOWOBJECTKIND :: StringObj:
            std::cout << "Cannot mod type<String> to type<String>\n";
            return NULL;
            break;
        default:
            std::cout << "Unknow MeowObj was passed\n";
            return NULL;
            break;
    }
}

void *String::onCmpE(MeowObject *b)
{
    switch(b->getKind())
    {
        case MEOWOBJECTKIND::IntObj:
        {
            std::cout << "Cannon add type<Integer> to type<String>\n";
            return NULL;
            break;
        }
        case MEOWOBJECTKIND::FloatObj:
        {
            std::cout << "Cannot add type<Float> to type<String>\n";
            return NULL;
            break;
        }
        case MEOWOBJECTKIND :: StringObj:
        {
            Integer *newVal = new Integer( ((((String *)b)->value == value) ), MEOWOBJECTKIND::IntObj);
            return newVal;
            break;
        }
        default:
        {
            std::cout << "Unknow MeowObj was passed\n";
            return NULL;
            break;
        }
    } 
}

void *String::onCmpL(MeowObject *b)
{
    switch(b->getKind())
    {
        case MEOWOBJECTKIND::IntObj:
        {
            std::cout << "Cannon add type<Integer> to type<String>\n";
            return NULL;
            break;
        }
        case MEOWOBJECTKIND::FloatObj:
        {
            std::cout << "Cannot add type<Float> to type<String>\n";
            return NULL;
            break;
        }
        case MEOWOBJECTKIND :: StringObj:
        {
            std::cout << "Cannot add type<Float> to type<String>\n";
            return NULL;
            break;
        }
        default:
        {
            std::cout << "Unknow MeowObj was passed\n";
            return NULL;
            break;
        }
    }
}

void *String::onCmpLE(MeowObject *b)
{
    switch(b->getKind())
    {
        case MEOWOBJECTKIND::IntObj:
        {
            std::cout << "Cannon add type<Integer> to type<String>\n";
            return NULL;
            break;
        }
        case MEOWOBJECTKIND::FloatObj:
        {
            std::cout << "Cannot add type<Float> to type<String>\n";
            return NULL;
            break;
        }
        case MEOWOBJECTKIND :: StringObj:
        {
            std::cout << "Cannot add type<Float> to type<String>\n";
            return NULL;
            break;
        }
        default:
        {
            std::cout << "Unknow MeowObj was passed\n";
            return NULL;
            break;
        }
    }
}

void *String::onCmpG(MeowObject *b)
{
    switch(b->getKind())
    {
        case MEOWOBJECTKIND::IntObj:
        {
            std::cout << "Cannon add type<Integer> to type<String>\n";
            return NULL;
            break;
        }
        case MEOWOBJECTKIND::FloatObj:
        {
            std::cout << "Cannot add type<Float> to type<String>\n";
            return NULL;
            break;
        }
        case MEOWOBJECTKIND :: StringObj:
        {
            std::cout << "Cannot add type<Float> to type<String>\n";
            return NULL;
            break;
        }
        default:
        {
            std::cout << "Unknow MeowObj was passed\n";
            return NULL;
            break;
        }
    }
}

void *String::onCmpGE(MeowObject *b)
{
    switch(b->getKind())
    {
        case MEOWOBJECTKIND::IntObj:
        {
            std::cout << "Cannon add type<Integer> to type<String>\n";
            return NULL;
            break;
        }
        case MEOWOBJECTKIND::FloatObj:
        {
            std::cout << "Cannot add type<Float> to type<String>\n";
            return NULL;
            break;
        }
        case MEOWOBJECTKIND :: StringObj:
        {
            std::cout << "Cannot add type<Float> to type<String>\n";
            return NULL;
            break;
        }
        default:
        {
            std::cout << "Unknow MeowObj was passed\n";
            return NULL;
            break;
        }
    }
}

void *String::onCmpNE(MeowObject *b)
{
    switch(b->getKind())
    {
        case MEOWOBJECTKIND::IntObj:
        {
            std::cout << "Cannon add type<Integer> to type<String>\n";
            return NULL;
            break;
        }
        case MEOWOBJECTKIND::FloatObj:
        {
            std::cout << "Cannot add type<Float> to type<String>\n";
            return NULL;
            break;
        }
        case MEOWOBJECTKIND :: StringObj:
        {
            Integer *newVal = new Integer( ((((String *)b)->value != value) ), MEOWOBJECTKIND::IntObj);
            return newVal;
            break;
        }
        default:
        {
            std::cout << "Unknow MeowObj was passed\n";
            return NULL;
            break;
        }
    }
}

void *String::onNegate()
{
    std::cout << "Cannot perform negate on type<string>\n";
    return nullptr;
}

void *String::onAnd(MeowObject *b)
{
    std::cout << "Cannot `and` with type<string>\n";
}

void *String::onOr(MeowObject *b)
{
    std::cout << "Cannot `or` with type<string>\n";
}
/*
**************************************************************************************
*                                                                                    *   
*                       FOR Float                                                    *
*                                                                                    * 
*                                                                                    *
**************************************************************************************
*/

void *Float::onAdd(MeowObject *b)
{
    switch(b->getKind())
    {
        case MEOWOBJECTKIND::IntObj:
        {
            Float *newVal = new Float((((Integer *)b)->value + value), MEOWOBJECTKIND::FloatObj);
            return newVal;
            break;
        }
        case MEOWOBJECTKIND::FloatObj:
        {
            Float *newVal = new Float((((Float *)b)->value + value), MEOWOBJECTKIND::FloatObj);
            return newVal;
            break;
        }
        case MEOWOBJECTKIND :: StringObj:
        {
            std::cout << "Cannot add type<Integer> to type<String>\n";
            return NULL;
            break;
        }
        default:
        {
            std::cout << "Unknow MeowObj was passed\n";
            return NULL;
            break;
        }
    }
}

void *Float::onSub(MeowObject *b)
{
    switch(b->getKind())
    {
        case MEOWOBJECTKIND::IntObj:
        {
            Float *newVal = new Float((((Integer *)b)->value - value), MEOWOBJECTKIND::FloatObj);
            return newVal;
            break;
        }
        case MEOWOBJECTKIND::FloatObj:
        {
            Float *newVal = new Float((((Float *)b)->value - value), MEOWOBJECTKIND::FloatObj);
            return newVal;
            break;
        }
        case MEOWOBJECTKIND :: StringObj:
        {
            std::cout << "Cannot substract type<Integer> to type<String>\n";
            return NULL;
            break;
        }
        default:
        {
            std::cout << "Unknow MeowObj was passed\n";
            return NULL;
            break;
        }
    }
}

void *Float::onMul(MeowObject *b)
{
    switch(b->getKind())
    {
        case MEOWOBJECTKIND::IntObj:
        {
            Float *newVal = new Float((((Integer *)b)->value * value), MEOWOBJECTKIND::FloatObj);
            return newVal;
            break;
        }
        
        case MEOWOBJECTKIND::FloatObj:
        {
            Float *newVal = new Float((((Float *)b)->value * value), MEOWOBJECTKIND::FloatObj);
            return newVal;
            break;
        }
        case MEOWOBJECTKIND :: StringObj:
        {
            std::cout << "Cannot multiply type<Integer> to type<String>\n";
            return NULL;
            break;
        }
        default:
        {
            std::cout << "Unknow MeowObj was passed\n";
            return NULL;
            break;
        }
    }
}

void *Float::onDiv(MeowObject *b)
{
    switch(b->getKind())
    {
        case MEOWOBJECTKIND::IntObj:
        {
            Float *newVal = new Float((((Integer *)b)->value / value), MEOWOBJECTKIND::FloatObj);
            return newVal;
            break;
        }
        case MEOWOBJECTKIND::FloatObj:
        {
            Float *newVal = new Float((((Float *)b)->value / value), MEOWOBJECTKIND::FloatObj);
            return newVal;
            break;
        }
        case MEOWOBJECTKIND::StringObj:
        {
            std::cout << "Cannot divide type<Integer> to type<String>\n";
            return NULL;
            break;
        }
        default:
        {
            std::cout << "Unknow MeowObj was passed\n";
            return NULL;
            break;
        }
    }
}

void *Float::onMod(MeowObject *b)
{
    switch(b->getKind())
    {
        case MEOWOBJECTKIND::IntObj:
        {
            Float *newVal = new Float((((Integer *)b)->value / value), MEOWOBJECTKIND::FloatObj);
            return newVal;
            break;
        }
        // this ( / ) is just a place holder needs to be changed with %
        case MEOWOBJECTKIND::FloatObj:
        {
            Float *newVal = new Float((((Float *)b)->value / value), MEOWOBJECTKIND::FloatObj);
            return newVal;
            break;
        }
        case MEOWOBJECTKIND :: StringObj:
        {
            std::cout << "Cannot mod type<Float> to type<String>\n";
            return NULL;
            break;
        }
        
        default:
        {
            std::cout << "Unknow MeowObj was passed\n";
            return NULL;
            break;
        }
    }
}

void *Float::onCmpE(MeowObject *b)
{
    switch(b->getKind())
    {
        case MEOWOBJECTKIND::IntObj:
        {
            Integer *newVal = new Integer((((Integer *)b)->value == value), MEOWOBJECTKIND::IntObj);
            return newVal;
            break;
        }
        case MEOWOBJECTKIND::FloatObj:
        {
            Integer *newVal = new Integer((((Integer *)b)->value == value), MEOWOBJECTKIND::IntObj);
            return newVal;
            break;
        }
        case MEOWOBJECTKIND :: StringObj:
        {
            std::cout << "Cannot add type<Integer> to type<String>\n";
            return NULL;
            break;
        }
        default:
        {
            std::cout << "Unknow MeowObj was passed\n";
            return NULL;
            break;
        }
    }
}

void *Float::onCmpNE(MeowObject *b)
{
    switch(b->getKind())
    {
        case MEOWOBJECTKIND::IntObj:
        {
            Integer *newVal = new Integer((((Integer *)b)->value != value), MEOWOBJECTKIND::IntObj);
            return newVal;
            break;
        }
        case MEOWOBJECTKIND::FloatObj:
        {
            Integer *newVal = new Integer((((Integer *)b)->value != value), MEOWOBJECTKIND::IntObj);
            return newVal;
            break;
        }
        case MEOWOBJECTKIND :: StringObj:
        {
            std::cout << "Cannot add type<Integer> to type<String>\n";
            return NULL;
            break;
        }
        default:
        {
            std::cout << "Unknow MeowObj was passed\n";
            return NULL;
            break;
        }
    }
}

void *Float::onCmpL(MeowObject *b)
{
    switch(b->getKind())
    {
        case MEOWOBJECTKIND::IntObj:
        {
            Integer *newVal = new Integer((((Integer *)b)->value < value), MEOWOBJECTKIND::IntObj);
            return newVal;
            break;
        }
        case MEOWOBJECTKIND::FloatObj:
        {
            Integer *newVal = new Integer((((Integer *)b)->value < value), MEOWOBJECTKIND::IntObj);
            return newVal;
            break;
        }
        case MEOWOBJECTKIND :: StringObj:
        {
            std::cout << "Cannot add type<Integer> to type<String>\n";
            return NULL;
            break;
        }
        default:
        {
            std::cout << "Unknow MeowObj was passed\n";
            return NULL;
            break;
        }
    }
}

void *Float::onCmpLE(MeowObject *b)
{
    switch(b->getKind())
    {
        case MEOWOBJECTKIND::IntObj:
        {
            Integer *newVal = new Integer((((Integer *)b)->value <= value), MEOWOBJECTKIND::IntObj);
            return newVal;
            break;
        }
        case MEOWOBJECTKIND::FloatObj:
        {
            Integer *newVal = new Integer((((Integer *)b)->value <= value), MEOWOBJECTKIND::IntObj);
            return newVal;
            break;
        }
        case MEOWOBJECTKIND :: StringObj:
        {
            std::cout << "Cannot add type<Integer> to type<String>\n";
            return NULL;
            break;
        }
        default:
        {
            std::cout << "Unknow MeowObj was passed\n";
            return NULL;
            break;
        }
    }
}

void *Float::onCmpG(MeowObject *b)
{
    switch(b->getKind())
    {
        case MEOWOBJECTKIND::IntObj:
        {
            Integer *newVal = new Integer((((Integer *)b)->value > value), MEOWOBJECTKIND::IntObj);
            return newVal;
            break;
        }
        case MEOWOBJECTKIND::FloatObj:
        {
            Integer *newVal = new Integer((((Integer *)b)->value > value), MEOWOBJECTKIND::IntObj);
            return newVal;
            break;
        }
        case MEOWOBJECTKIND :: StringObj:
        {
            std::cout << "Cannot add type<Integer> to type<String>\n";
            return NULL;
            break;
        }
        default:
        {
            std::cout << "Unknow MeowObj was passed\n";
            return NULL;
            break;
        }
    }
}

void *Float::onCmpGE(MeowObject *b)
{
    switch(b->getKind())
    {
        case MEOWOBJECTKIND::IntObj:
        {
            Integer *newVal = new Integer((((Integer *)b)->value >= value), MEOWOBJECTKIND::IntObj);
            return newVal;
            break;
        }
        case MEOWOBJECTKIND::FloatObj:
        {
            Integer *newVal = new Integer((((Integer *)b)->value >= value), MEOWOBJECTKIND::IntObj);
            return newVal;
            break;
        }
        case MEOWOBJECTKIND :: StringObj:
        {
            std::cout << "Cannot add type<Integer> to type<String>\n";
            return NULL;
            break;
        }
        default:
        {
            std::cout << "Unknow MeowObj was passed\n";
            return NULL;
            break;
        }
    }
}

void *Float::onNegate()
{
    Float *newVal = new Float( -value, MEOWOBJECTKIND::FloatObj);
    return newVal;
}

void *Float::onAnd(MeowObject *b)
{
    return new Integer( ((Integer *)b)->value && value , MEOWOBJECTKIND::IntObj);
}

void *Float::onOr(MeowObject *b)
{
    return new Integer( ((Integer *)b)->value || value , MEOWOBJECTKIND::IntObj);
}