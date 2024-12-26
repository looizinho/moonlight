import { Meteor } from 'meteor/meteor';
import { WebApp } from 'meteor/webapp'
import { WebSocket, WebSocketServer } from 'ws';

// Cria nosso servidor WS
const WSServer = new WebSocketServer({ noServer: true })

// Cria nosso cliente WS do lado do servidor (meio inútil, está só por questão acadêmica)
const WSClient = new WebSocket('wss://mac.tail17794.ts.net:443/microcontrollers')

Meteor.startup(() => {
  // *** SERVIDOR *** //
  // ESCUTA POR UMA CONEXÃO
  WSServer.on('connection', (ws, request) => {
    if (request.url === '/microcontrollers') {
      const authHeader = request.headers['authorization'];

      // Se não for autenticado, encerra a conexão
      if (!isValidCredentials(authHeader)) {
        ws.close(1008, 'Unauthorized'); // Código 1008: Policy Violation
        console.log(`Connection rejected on ${request.url}`);
        return;
      }
      console.log(`${request.url === '/microcontrollers' ? 'MICROCONTROLADOR' : 'WEBAPP'} CONECTADO!`);
    } else {
      console.log(`Connection established on ${request.url} (no authentication required)`);
    }

    // ESCUTA POR UMA NOVA MENSAGEM
    ws.on('message', (msg) => {
      let json = JSON.parse(msg) // PARSEIA A STRING PARA UM JSON
      console.log(`[${json.name}] Mensagem recebida de ${json.from} com a mensagem "${json.message}" em ${json.dateTime}`);
      // console.info(json);
      ws.send("Message received!")
    })

    ws.on('ping', () => {
      console.log('PING recebido!');

    })

    ws.on('close', () => {
      console.error('Client Closed!');
    })

    Meteor.setInterval(() => {
      // ws.send(JSON.stringify(request))
      // ws.ping();
    }, 3000)
  })

  // *** CLIENTE *** //
  // QUANDO A CONEXÃO FOR ABERTA
  WSClient.onopen = () => {
    console.log('CONEXÃO WS ABERTA');

    // DELAY DE 5 SEGUNDOS
    Meteor.setTimeout(() => {
      // ENVIA UMA MENSAGEM PRO SERVIDOR
      WSClient.send(JSON.stringify( // CONVERTE JSON EM STRING
        {
          from: 'Server',
          message: 'Hello Server!',
          dateTime: new Date()
        }
      ))
    }, 5000)
  }
});

// Código para nosso WebSocket não conflitar com o WS interno do Meteor.
// Toda a comunicação será pelo path '/microcontrollers'
WebApp.httpServer.on('upgrade', (request, socket, head) => {
  if (request.url === '/microcontrollers') {
    WSServer.handleUpgrade(request, socket, head, (ws) => {
      WSServer.emit('connection', ws, request)
    })
  }
})

// Função para validar credenciais
function isValidCredentials(authHeader) {
  if (!authHeader || !authHeader.startsWith('Basic ')) return false;

  const base64Credentials = authHeader.split(' ')[1];
  const credentials = Buffer.from(base64Credentials, 'base64').toString('ascii');
  const [username, password] = credentials.split(':');

  return username === 'itamar' && password === 'nanotecc'; // Substitua por lógica real
}