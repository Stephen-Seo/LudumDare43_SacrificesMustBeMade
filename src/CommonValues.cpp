#include "CommonValues.hpp"

void Context::playSfx(const unsigned int& id)
{
    try
    {
        sf::SoundBuffer& buf = sfxMap.at(id);
        for(auto iter = soundPool.begin(); iter != soundPool.end(); ++iter)
        {
            if(iter->getStatus() != sf::SoundSource::Playing)
            {
                iter->setBuffer(buf);
                iter->play();
                break;
            }
        }
    } catch(const std::out_of_range& e)
    {
        fprintf(stderr, "ERROR: Context::playSfx got invalid sound id \"%d\"!", id);
    }
}
