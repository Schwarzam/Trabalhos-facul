import requests
from bs4 import BeautifulSoup
import pandas as pd

def extract_tables_from_url(url):
    # Fetch the HTML content
    response = requests.get(url)
    html_content = response.content

    soup = BeautifulSoup(html_content, 'html.parser')
    tables = soup.find_all('table', class_='table-auto w-full text-xs leading-loose')

    dataframes = []
    for table in tables:
        df = pd.read_html(str(table))[0]
        dataframes.append(df)
    
    return dataframes



if __name__ == '__main__':
    
    url = 'https://programming-language-benchmarks.vercel.app/python-vs-rust'
    dataframes = extract_tables_from_url(url)

    
    
    import pandas as pd
    concatenated = pd.concat(dataframes, axis=0, ignore_index=True)
    
    print(concatenated[2])
    
    
    
    
