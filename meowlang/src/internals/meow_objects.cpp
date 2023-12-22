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
        case MEOWOBJECTKIND::Meow_IntObj:
        {
            Integer *newVal = new Integer((((Integer *)b)->value + value), MEOWOBJECTKIND::Meow_IntObj);
            return newVal;
            break;
        }
        case MEOWOBJECTKIND::Meow_FloatObj:
        {
            Float *newVal = new Float((((Float *)b)->value + value), MEOWOBJECTKIND::Meow_FloatObj);
            return newVal;
            break;
        }
        case MEOWOBJECTKIND :: Meow_StringObj:
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
        case MEOWOBJECTKIND::Meow_IntObj:
        {
            Integer *newVal = new Integer((((Integer *)b)->value - value), MEOWOBJECTKIND::Meow_IntObj);
            return newVal;
            break;
        }
        case MEOWOBJECTKIND::Meow_FloatObj:
        {
            Float *newVal = new Float((((Float *)b)->value - value), MEOWOBJECTKIND::Meow_FloatObj);
            return newVal;
            break;
        }
        case MEOWOBJECTKIND :: Meow_StringObj:
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
        case MEOWOBJECTKIND::Meow_IntObj:
        {
            Integer *newVal = new Integer((((Integer *)b)->value * value), MEOWOBJECTKIND::Meow_IntObj);
            return newVal;
            break;
        }
        case MEOWOBJECTKIND::Meow_FloatObj:
        {
            Float *newVal = new Float((((Float *)b)->value * value), MEOWOBJECTKIND::Meow_FloatObj);
            return newVal;
            break;
        }
        case MEOWOBJECTKIND :: Meow_StringObj:
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
        case MEOWOBJECTKIND::Meow_IntObj:
        {
            Float *newVal = new Float((((Integer *)b)->value / value), MEOWOBJECTKIND::Meow_FloatObj);
            return newVal;
            break;
        }
        case MEOWOBJECTKIND::Meow_FloatObj:
        {
            Float *newVal = new Float((((Float *)b)->value / value), MEOWOBJECTKIND::Meow_FloatObj);
            return newVal;
            break;
        }
        case MEOWOBJECTKIND :: Meow_StringObj:
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
        case MEOWOBJECTKIND::Meow_IntObj:
        {
            Integer *newVal = new Integer((((Integer *)b)->value % value), MEOWOBJECTKIND::Meow_IntObj);
            return newVal;
            break;
        }
        // this ( / ) is just a place holder needs to be changed with %
        case MEOWOBJECTKIND::Meow_FloatObj:
        {
            Float *newVal = new Float((((Float *)b)->value / value), MEOWOBJECTKIND::Meow_FloatObj);
            return newVal;
            break;
        }
        case MEOWOBJECTKIND :: Meow_StringObj:
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
        case MEOWOBJECTKIND::Meow_IntObj:
        {
            Integer *newVal = new Integer(( ((Integer *)b)->value == value ), MEOWOBJECTKIND::Meow_IntObj);
            return newVal;
            break;
        }
        // this ( / ) is just a place holder needs to be changed with %
        case MEOWOBJECTKIND::Meow_FloatObj:
        {
            Float *newVal = new Float(( ((Float *)b)->value == value ), MEOWOBJECTKIND::Meow_FloatObj);
            return newVal;
            break;
        }
        case MEOWOBJECTKIND :: Meow_StringObj:
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
        case MEOWOBJECTKIND::Meow_IntObj:
        {
            Integer *newVal = new Integer(( ((Integer *)b)->value != value ), MEOWOBJECTKIND::Meow_IntObj);
            return newVal;
            break;
        }
        // this ( / ) is just a place holder needs to be changed with %
        case MEOWOBJECTKIND::Meow_FloatObj:
        {
            Integer *newVal = new Integer(( ((Float *)b)->value != value ), MEOWOBJECTKIND::Meow_IntObj);
            return newVal;
            break;
        }
        case MEOWOBJECTKIND :: Meow_StringObj:
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
        case MEOWOBJECTKIND::Meow_IntObj:
        {
            Integer *newVal = new Integer(( ((Integer *)b)->value < value ), MEOWOBJECTKIND::Meow_IntObj);
            return newVal;
            break;
        }
        // this ( / ) is just a place holder needs to be changed with %
        case MEOWOBJECTKIND::Meow_FloatObj:
        {
            Integer *newVal = new Integer(( ((Float *)b)->value < value ), MEOWOBJECTKIND::Meow_IntObj);
            return newVal;
            break;
        }
        case MEOWOBJECTKIND :: Meow_StringObj:
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
        case MEOWOBJECTKIND::Meow_IntObj:
        {
            Integer *newVal = new Integer(( ((Integer *)b)->value <= value ), MEOWOBJECTKIND::Meow_IntObj);
            return newVal;
            break;
        }
        // this ( / ) is just a place holder needs to be changed with %
        case MEOWOBJECTKIND::Meow_FloatObj:
        {
            Integer *newVal = new Integer(( ((Float *)b)->value <= value ), MEOWOBJECTKIND::Meow_IntObj);
            return newVal;
            break;
        }
        case MEOWOBJECTKIND :: Meow_StringObj:
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
        case MEOWOBJECTKIND::Meow_IntObj:
        {
            Integer *newVal = new Integer(( ((Integer *)b)->value > value ), MEOWOBJECTKIND::Meow_IntObj);
            return newVal;
            break;
        }
        // this ( / ) is just a place holder needs to be changed with %
        case MEOWOBJECTKIND::Meow_FloatObj:
        {
            Integer *newVal = new Integer(( ((Float *)b)->value > value ), MEOWOBJECTKIND::Meow_IntObj);
            return newVal;
            break;
        }
        case MEOWOBJECTKIND :: Meow_StringObj:
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
        case MEOWOBJECTKIND::Meow_IntObj:
        {
            Integer *newVal = new Integer(( ((Integer *)b)->value >= value ), MEOWOBJECTKIND::Meow_IntObj);
            return newVal;
            break;
        }
        // this ( / ) is just a place holder needs to be changed with %
        case MEOWOBJECTKIND::Meow_FloatObj:
        {
            Integer *newVal = new Integer(( ((Float *)b)->value >= value ), MEOWOBJECTKIND::Meow_IntObj);
            return newVal;
            break;
        }
        case MEOWOBJECTKIND :: Meow_StringObj:
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
    Integer *newVal = new Integer( -value, MEOWOBJECTKIND::Meow_IntObj);
    return newVal;
}

void *Integer::onAnd(MeowObject *b)
{
    return new Integer( ((Integer *)b)->value && value , MEOWOBJECTKIND::Meow_IntObj);
}

void *Integer::onOr(MeowObject *b)
{
    return new Integer( ((Integer *)b)->value || value , MEOWOBJECTKIND::Meow_IntObj);
}

void *Integer::onNot()
{
    return new Integer( !value, MEOWOBJECTKIND::Meow_IntObj);
}

void *Integer::getAtIndex(uint64_t idx)
{
    std::cout << "Cannot perform `[]` on integers\n";
    exit(0);
}

void *Integer::setAtIndex(uint64_t idx, MeowObject *b)
{
    std::cout << "Cannot perform index operations in type<Integer>\n";
    exit(0);
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
        case MEOWOBJECTKIND::Meow_IntObj:
        {
            std::cout << "Cannon add type<Integer> to type<String>\n";
            return NULL;
            break;
        }
        case MEOWOBJECTKIND::Meow_FloatObj:
        {
            std::cout << "Cannot add type<Float> to type<String>\n";
            return NULL;
            break;
        }
        case MEOWOBJECTKIND :: Meow_StringObj:
        {
            String *newVal = new String((((String *)b)->value + value), MEOWOBJECTKIND::Meow_StringObj);
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
        case MEOWOBJECTKIND::Meow_IntObj:
        {
            std::cout << "Cannon substrace type<Integer> to type<String>\n";
            return NULL;
            break;
        }
        case MEOWOBJECTKIND::Meow_FloatObj:
        {
            std::cout << "Cannot substrace type<Float> to type<String>\n";
            return NULL;
            break;
        }
        case MEOWOBJECTKIND :: Meow_StringObj:
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
        case MEOWOBJECTKIND::Meow_IntObj:
        {
            std::cout << "Cannon multiply type<Integer> to type<String>\n";
            return NULL;
            break;
        }
        case MEOWOBJECTKIND::Meow_FloatObj:
        {
            std::cout << "Cannot multiply type<Float> to type<String>\n";
            return NULL;
            break;
        }
        case MEOWOBJECTKIND :: Meow_StringObj:
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
        case MEOWOBJECTKIND::Meow_IntObj:
        {
            std::cout << "Cannon div type<Integer> to type<String>\n";
            return NULL;
            break;
        }
        case MEOWOBJECTKIND::Meow_FloatObj:
        {
            std::cout << "Cannot div type<Float> to type<String>\n";
            return NULL;
            break;
        }
        case MEOWOBJECTKIND :: Meow_StringObj:
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
        case MEOWOBJECTKIND::Meow_IntObj:
            std::cout << "Cannon add type<Integer> to type<String>\n";
            return NULL;
            break;
        case MEOWOBJECTKIND::Meow_FloatObj:
            std::cout << "Cannot add type<Float> to type<String>\n";
            return NULL;
            break;
        case MEOWOBJECTKIND :: Meow_StringObj:
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
        case MEOWOBJECTKIND::Meow_IntObj:
        {
            std::cout << "Cannon add type<Integer> to type<String>\n";
            return NULL;
            break;
        }
        case MEOWOBJECTKIND::Meow_FloatObj:
        {
            std::cout << "Cannot add type<Float> to type<String>\n";
            return NULL;
            break;
        }
        case MEOWOBJECTKIND :: Meow_StringObj:
        {
            Integer *newVal = new Integer( ((((String *)b)->value == value) ), MEOWOBJECTKIND::Meow_IntObj);
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
        case MEOWOBJECTKIND::Meow_IntObj:
        {
            std::cout << "Cannon add type<Integer> to type<String>\n";
            return NULL;
            break;
        }
        case MEOWOBJECTKIND::Meow_FloatObj:
        {
            std::cout << "Cannot add type<Float> to type<String>\n";
            return NULL;
            break;
        }
        case MEOWOBJECTKIND :: Meow_StringObj:
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
        case MEOWOBJECTKIND::Meow_IntObj:
        {
            std::cout << "Cannon add type<Integer> to type<String>\n";
            return NULL;
            break;
        }
        case MEOWOBJECTKIND::Meow_FloatObj:
        {
            std::cout << "Cannot add type<Float> to type<String>\n";
            return NULL;
            break;
        }
        case MEOWOBJECTKIND :: Meow_StringObj:
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
        case MEOWOBJECTKIND::Meow_IntObj:
        {
            std::cout << "Cannon add type<Integer> to type<String>\n";
            return NULL;
            break;
        }
        case MEOWOBJECTKIND::Meow_FloatObj:
        {
            std::cout << "Cannot add type<Float> to type<String>\n";
            return NULL;
            break;
        }
        case MEOWOBJECTKIND :: Meow_StringObj:
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
        case MEOWOBJECTKIND::Meow_IntObj:
        {
            std::cout << "Cannon add type<Integer> to type<String>\n";
            return NULL;
            break;
        }
        case MEOWOBJECTKIND::Meow_FloatObj:
        {
            std::cout << "Cannot add type<Float> to type<String>\n";
            return NULL;
            break;
        }
        case MEOWOBJECTKIND :: Meow_StringObj:
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
        case MEOWOBJECTKIND::Meow_IntObj:
        {
            std::cout << "Cannon add type<Integer> to type<String>\n";
            return NULL;
            break;
        }
        case MEOWOBJECTKIND::Meow_FloatObj:
        {
            std::cout << "Cannot add type<Float> to type<String>\n";
            return NULL;
            break;
        }
        case MEOWOBJECTKIND :: Meow_StringObj:
        {
            Integer *newVal = new Integer( ((((String *)b)->value != value) ), MEOWOBJECTKIND::Meow_IntObj);
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
    return NULL;
}

void *String::onAnd(MeowObject *b)
{
    std::cout << "Cannot `and` with type<string>\n";
    return NULL;
}

void *String::onOr(MeowObject *b)
{
    std::cout << "Cannot `or` with type<string>\n";
    return NULL;
}

void *String::onNot()
{
    std::cout << "Cannot perform not on type<string>\n";
    return NULL;
}

void *String::getAtIndex(uint64_t idx)
{
    if(idx > value.size() || idx < 0)
    {
        std::cout << "Index out of range\n";
        exit(0);
    }
    std::string v = std::string(1, value[idx]);
    String *retVal = new String(v, MEOWOBJECTKIND::Meow_StringObj);
    return retVal;
}

void *String::setAtIndex(uint64_t idx,  MeowObject *b)
{
    if(idx > value.size() || idx < 0)
    {
        std::cout << "Index out of range\n";
        exit(0);
    }

    switch (b->getKind())
    {
    case MEOWOBJECTKIND::Meow_IntObj :
    case MEOWOBJECTKIND::Meow_FloatObj:
    case MEOWOBJECTKIND::Meow_VarObj:
        std::cout << "Cannot assign int to a type<string>\n";
        exit(0);
        break;
    
    default:
        break;
    }

    value[idx] = *(char *)((String *)b)->value.c_str();

    return NULL;
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
        case MEOWOBJECTKIND::Meow_IntObj:
        {
            Float *newVal = new Float((((Integer *)b)->value + value), MEOWOBJECTKIND::Meow_FloatObj);
            return newVal;
            break;
        }
        case MEOWOBJECTKIND::Meow_FloatObj:
        {
            Float *newVal = new Float((((Float *)b)->value + value), MEOWOBJECTKIND::Meow_FloatObj);
            return newVal;
            break;
        }
        case MEOWOBJECTKIND :: Meow_StringObj:
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
        case MEOWOBJECTKIND::Meow_IntObj:
        {
            Float *newVal = new Float((((Integer *)b)->value - value), MEOWOBJECTKIND::Meow_FloatObj);
            return newVal;
            break;
        }
        case MEOWOBJECTKIND::Meow_FloatObj:
        {
            Float *newVal = new Float((((Float *)b)->value - value), MEOWOBJECTKIND::Meow_FloatObj);
            return newVal;
            break;
        }
        case MEOWOBJECTKIND :: Meow_StringObj:
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
        case MEOWOBJECTKIND::Meow_IntObj:
        {
            Float *newVal = new Float((((Integer *)b)->value * value), MEOWOBJECTKIND::Meow_FloatObj);
            return newVal;
            break;
        }
        
        case MEOWOBJECTKIND::Meow_FloatObj:
        {
            Float *newVal = new Float((((Float *)b)->value * value), MEOWOBJECTKIND::Meow_FloatObj);
            return newVal;
            break;
        }
        case MEOWOBJECTKIND :: Meow_StringObj:
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
        case MEOWOBJECTKIND::Meow_IntObj:
        {
            Float *newVal = new Float((((Integer *)b)->value / value), MEOWOBJECTKIND::Meow_FloatObj);
            return newVal;
            break;
        }
        case MEOWOBJECTKIND::Meow_FloatObj:
        {
            Float *newVal = new Float((((Float *)b)->value / value), MEOWOBJECTKIND::Meow_FloatObj);
            return newVal;
            break;
        }
        case MEOWOBJECTKIND::Meow_StringObj:
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
        case MEOWOBJECTKIND::Meow_IntObj:
        {
            Float *newVal = new Float((((Integer *)b)->value / value), MEOWOBJECTKIND::Meow_FloatObj);
            return newVal;
            break;
        }
        // this ( / ) is just a place holder needs to be changed with %
        case MEOWOBJECTKIND::Meow_FloatObj:
        {
            Float *newVal = new Float((((Float *)b)->value / value), MEOWOBJECTKIND::Meow_FloatObj);
            return newVal;
            break;
        }
        case MEOWOBJECTKIND :: Meow_StringObj:
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
        case MEOWOBJECTKIND::Meow_IntObj:
        {
            Integer *newVal = new Integer((((Integer *)b)->value == value), MEOWOBJECTKIND::Meow_IntObj);
            return newVal;
            break;
        }
        case MEOWOBJECTKIND::Meow_FloatObj:
        {
            Integer *newVal = new Integer((((Integer *)b)->value == value), MEOWOBJECTKIND::Meow_IntObj);
            return newVal;
            break;
        }
        case MEOWOBJECTKIND :: Meow_StringObj:
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
        case MEOWOBJECTKIND::Meow_IntObj:
        {
            Integer *newVal = new Integer((((Integer *)b)->value != value), MEOWOBJECTKIND::Meow_IntObj);
            return newVal;
            break;
        }
        case MEOWOBJECTKIND::Meow_FloatObj:
        {
            Integer *newVal = new Integer((((Integer *)b)->value != value), MEOWOBJECTKIND::Meow_IntObj);
            return newVal;
            break;
        }
        case MEOWOBJECTKIND :: Meow_StringObj:
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
        case MEOWOBJECTKIND::Meow_IntObj:
        {
            Integer *newVal = new Integer((((Integer *)b)->value < value), MEOWOBJECTKIND::Meow_IntObj);
            return newVal;
            break;
        }
        case MEOWOBJECTKIND::Meow_FloatObj:
        {
            Integer *newVal = new Integer((((Integer *)b)->value < value), MEOWOBJECTKIND::Meow_IntObj);
            return newVal;
            break;
        }
        case MEOWOBJECTKIND :: Meow_StringObj:
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
        case MEOWOBJECTKIND::Meow_IntObj:
        {
            Integer *newVal = new Integer((((Integer *)b)->value <= value), MEOWOBJECTKIND::Meow_IntObj);
            return newVal;
            break;
        }
        case MEOWOBJECTKIND::Meow_FloatObj:
        {
            Integer *newVal = new Integer((((Integer *)b)->value <= value), MEOWOBJECTKIND::Meow_IntObj);
            return newVal;
            break;
        }
        case MEOWOBJECTKIND :: Meow_StringObj:
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
        case MEOWOBJECTKIND::Meow_IntObj:
        {
            Integer *newVal = new Integer((((Integer *)b)->value > value), MEOWOBJECTKIND::Meow_IntObj);
            return newVal;
            break;
        }
        case MEOWOBJECTKIND::Meow_FloatObj:
        {
            Integer *newVal = new Integer((((Integer *)b)->value > value), MEOWOBJECTKIND::Meow_IntObj);
            return newVal;
            break;
        }
        case MEOWOBJECTKIND :: Meow_StringObj:
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
        case MEOWOBJECTKIND::Meow_IntObj:
        {
            Integer *newVal = new Integer((((Integer *)b)->value >= value), MEOWOBJECTKIND::Meow_IntObj);
            return newVal;
            break;
        }
        case MEOWOBJECTKIND::Meow_FloatObj:
        {
            Integer *newVal = new Integer((((Integer *)b)->value >= value), MEOWOBJECTKIND::Meow_IntObj);
            return newVal;
            break;
        }
        case MEOWOBJECTKIND :: Meow_StringObj:
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
    Float *newVal = new Float( -value, MEOWOBJECTKIND::Meow_FloatObj);
    return newVal;
}

void *Float::onAnd(MeowObject *b)
{
    return new Integer( ((Integer *)b)->value && value , MEOWOBJECTKIND::Meow_IntObj);
}

void *Float::onOr(MeowObject *b)
{
    return new Integer( ((Integer *)b)->value || value , MEOWOBJECTKIND::Meow_IntObj);
}

void *Float::onNot()
{
    return new Integer( !value, MEOWOBJECTKIND::Meow_IntObj);
}

void *Float::getAtIndex(uint64_t idx)
{
    std::cout << "Cannot perform `[]` on float\n";
    exit(0);
}

void *Float::setAtIndex(uint64_t idx, MeowObject *b)
{
    std::cout << "Cannot perform index operations in type<Float>\n";
    exit(0);
}


/*
***********************************************************************************
*                                                                                 *
*                                                                                 *
*                   ARRAY OBJ                                                     *
*                                                                                 *
***********************************************************************************
*/

void *ArrayObj::onAdd(MeowObject *b)
{
    switch (b->getKind())
    {
    case MEOWOBJECTKIND::Meow_IntObj :
    {
        int i = 0;

        while(i < values.size())
        {
            values[i] = (MeowObject *)values[i]->onAdd(b);
            i++;
        }
        break;
    }
    case MEOWOBJECTKIND::Meow_FloatObj :
    {
        int i = 0;

        while(i < values.size())
        {
            values[i] = (MeowObject *)values[i]->onAdd(b);
            i++;
        }
        break;
    }
    case MEOWOBJECTKIND::Meow_StringObj :
    {
        std::cout << "Canot add string to array\n";
        break;
    }
    default:
        break;
    }

    return NULL;
}

void *ArrayObj::onSub(MeowObject *b)
{
    switch (b->getKind())
    {
    case MEOWOBJECTKIND::Meow_IntObj :
    {
        int i = 0;

        while(i < values.size())
        {
            values[i] = (MeowObject *)values[i]->onSub(b);
            i++;
        }
        break;
    }
    case MEOWOBJECTKIND::Meow_FloatObj :
    {
        int i = 0;

        while(i < values.size())
        {
            values[i] = (MeowObject *)values[i]->onSub(b);
            i++;
        }
        break;
    }
    case MEOWOBJECTKIND::Meow_StringObj :
        std::cout << "Canot add string to array\n";
        break;
    
    default:
        break;
    }

    return NULL;
}
void *ArrayObj::onMod(MeowObject *b)
{
    switch (b->getKind())
    {
    case MEOWOBJECTKIND::Meow_IntObj :
    {
        int i = 0;

        while(i < values.size())
        {
            values[i] = (MeowObject *)values[i]->onMod(b);
            i++;
        }
        break;
    }
    case MEOWOBJECTKIND::Meow_FloatObj :
    {
        int i = 0;

        while(i < values.size())
        {
            values[i] = (MeowObject *)values[i]->onMod(b);
            i++;
        }
        break;
    }
    case MEOWOBJECTKIND::Meow_StringObj :
        std::cout << "Canot add string to array\n";
        break;
    
    default:
        break;
    }

    return NULL;
}

void *ArrayObj::onMul(MeowObject *b)
{
    switch (b->getKind())
    {
    case MEOWOBJECTKIND::Meow_IntObj :
    {
        int i = 0;

        while(i < values.size())
        {
            values[i] = (MeowObject *)values[i]->onMul(b);
            i++;
        }
        break;
    }
    case MEOWOBJECTKIND::Meow_FloatObj :
    {
        int i = 0;

        while(i < values.size())
        {
            values[i] = (MeowObject *)values[i]->onMul(b);
            i++;
        }
        break;
    }
    case MEOWOBJECTKIND::Meow_StringObj :
        std::cout << "Canot add string to array\n";
        break;
    
    default:
        break;
    }

    return NULL;
}

void *ArrayObj::onDiv(MeowObject *b)
{
    switch (b->getKind())
    {
    case MEOWOBJECTKIND::Meow_IntObj :
    {
        int i = 0;

        while(i < values.size())
        {
            values[i] = (MeowObject *)values[i]->onDiv(b);
            i++;
        }
        break;
    }
    case MEOWOBJECTKIND::Meow_FloatObj :
    {
        int i = 0;

        while(i < values.size())
        {
            values[i] = (MeowObject *)values[i]->onDiv(b);
            i++;
        }
        break;
    }
    case MEOWOBJECTKIND::Meow_StringObj :
        std::cout << "Canot add string to array\n";
        break;
    
    default:
        break;
    }

    return NULL;
}

void *ArrayObj::onCmpE(MeowObject *a)
{
    std::cout << "Cannot compare array\n";
    exit(0);
}

void *ArrayObj::onCmpNE(MeowObject *a)
{
    std::cout << "Cannot compare array\n";
    exit(0);
}

void *ArrayObj::onCmpL(MeowObject *a)
{
    std::cout << "Cannot compare array\n";
    exit(0);
}

void *ArrayObj::onCmpLE(MeowObject *a)
{
    std::cout << "Cannot compare array\n";
    exit(0);
}

void *ArrayObj::onCmpG(MeowObject *a)
{
    std::cout << "Cannot compare array\n";
    exit(0);
}

void *ArrayObj::onCmpGE(MeowObject *a)
{
    std::cout << "Cannot compare array\n";
    exit(0);
}

void *ArrayObj::onNegate()
{
    std::cout << "Cannot compare array\n";
    exit(0);
}

void *ArrayObj::onNot()
{
    std::cout << "Cannot compare array\n";
    exit(0);
}

void *ArrayObj::getAtIndex(uint64_t idx)
{
    if(idx > values.size() || idx < 0)
    {
        std::cout << "Index out of range\n";
        exit(0);
        return NULL;
    }

    return values[idx];
}

void *ArrayObj::setAtIndex(uint64_t idx,  MeowObject *b)
{
    if(idx > values.size() && idx < 0)
    {
        std::cout << "Index out of range\n";
        exit(0);
        return 0;
    }

    values[idx] = b;

    return NULL;
}

void *ArrayObj::onAnd(MeowObject *b)
{
    std::cout << "Cannot and an array object\n";
    exit(0);
}

void *ArrayObj::onOr(MeowObject *b)
{
    std::cout << "Cannot or an array object\n";
    exit(0);
}