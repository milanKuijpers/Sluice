#ifndef IUSERACTIONS_H
#define IUSERACTIONS_H

class iUserActions
{
public:
    virtual ~iUserActions() {};

    virtual void StartPressed() = 0;
    virtual void VrijgevenVoorUitvarenPressed() = 0;
    virtual void VrijgevenVoorInvarenPressed() = 0;
    virtual void AlarmPressed() = 0;
    virtual void HerstelPressed() = 0;
};

#endif
