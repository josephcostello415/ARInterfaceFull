from pyowm import OWM
from pyowm.utils import config
from pyowm.utils import timestamps


def getTemp():
	owm = OWM('8ec4b75510768f7093dc719e515447e6')
	mgr = owm.weather_manager()

	observation = mgr.weather_at_place('Newport News')
	w = observation.weather

	w.detailed_status         
	w.wind()                  
	w.humidity                
	w.temperature('fahrenheit')  
	w.rain                    
	w.heat_index              
	w.clouds                  

	current = w.temperature('fahrenheit').get('temp')
	print(w.temperature('celsius'))
	print(w.status)
	print(w.temperature('fahrenheit'))
	print(current)
	return current

def getWeather():
	owm = OWM('8ec4b75510768f7093dc719e515447e6')
	mgr = owm.weather_manager()

	observation = mgr.weather_at_place('Newport News')
	w = observation.weather
	weather = w.status
	return weather